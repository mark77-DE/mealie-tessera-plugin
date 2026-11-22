#!/usr/bin/env python3
"""Run the Tessera Preview Bench with live Home Assistant service responses.

Required environment:
  TESSERA_HA_URL   e.g. http://homeassistant.local:8123
  TESSERA_HA_TOKEN a Home Assistant long-lived access token

The official Tessera firmware checkout is kept separately and patched locally;
no files in the official tessera-plugins checkout are changed.
"""
from __future__ import annotations

import os
import shutil
import subprocess
import sys
from pathlib import Path

MARKER = "# MARK77_LIVE_HOME_ASSISTANT_PREVIEW"
TREE = Path(os.environ.get("TESSERA_HA_PREVIEW_TREE", "~/.cache/tessera-ha-preview")).expanduser()
REPOSITORY = "https://github.com/MaxGramser/homeassistant_espscreen.git"


def fail(message: str, code: int = 2) -> None:
    raise SystemExit(f"HA preview: {message}")


def patch_bench(preview_repo: Path) -> tuple[Path, str]:
    bench = preview_repo / "tools" / "bench.py"
    source = bench.read_text(encoding="utf-8")
    if MARKER in source:
        fail(f"{bench} already contains a live-preview patch; restore the original file before continuing")

    import_line = "import yaml\n"
    if import_line not in source:
        fail(f"cannot find expected import point in {bench}")
    source = source.replace(import_line, import_line + "import aiohttp\n", 1)

    helper = r'''
# MARK77_LIVE_HOME_ASSISTANT_PREVIEW
async def live_ha_service(base_url, token, ask, service_data):
    """Call a response-capable Home Assistant service through its authenticated REST API."""
    import json
    from urllib.parse import quote

    if not isinstance(ask, str) or not ask.startswith("call_service:"):
        raise ValueError("not a Home Assistant service request")
    service_name = ask[len("call_service:"):]
    if "." not in service_name:
        raise ValueError(f"invalid service name: {service_name}")
    domain, service = service_name.split(".", 1)
    url = base_url.rstrip("/") + "/api/services/" + quote(domain, safe="") + "/" + quote(service, safe="") + "?return_response"
    timeout = aiohttp.ClientTimeout(total=30)
    headers = {"Authorization": "Bearer " + token, "Content-Type": "application/json"}
    async with aiohttp.ClientSession(timeout=timeout) as session:
        async with session.post(url, headers=headers, json=service_data or {}) as response:
            raw = await response.text()
            if response.status >= 400:
                raise RuntimeError(f"Home Assistant returned HTTP {response.status}: {raw[:300]}")
            try:
                payload = json.loads(raw)
            except ValueError as error:
                raise RuntimeError("Home Assistant returned invalid JSON") from error
    service_response = payload.get("service_response") if isinstance(payload, dict) else None
    if isinstance(service_response, dict):
        key = domain + "." + service
        if key in service_response:
            return service_response[key]
        if len(service_response) == 1:
            return next(iter(service_response.values()))
    if isinstance(payload, dict) and "service_response" in payload:
        return service_response
    raise RuntimeError("Home Assistant did not return service_response; check that this action supports response data")


'''
    class_marker = "# ---- one screen's program\n\nclass Bench(run.Run):"
    if class_marker not in source:
        fail("cannot find Bench class insertion point; the upstream preview tool may have changed")
    source = source.replace(class_marker, helper + class_marker, 1)

    old = '''        elif ask not in self.entry.manifest['permissions']['ha_commands']:
            reply.update(ok=False, error='not_allowed')
            self.find('warning', 'questions', f'asked {ask!r}, which permissions.ha_commands does not name: the app refuses it')
        elif ask not in commands:
            reply.update(ok=False, error='no answer in preview.yaml')
            self.find('info', 'questions', f'asked {ask!r}; preview.yaml has no answer under commands, so it got none')
        else:
            result = moments(commands[ask], self.spec.get('time_zone') or ZONE, self.now)
            reply.update(ok=True, result=answer_of(self.entry, ask, result, self.spec.get('time_zone') or ZONE))
'''
    new = '''        elif ask not in self.entry.manifest['permissions']['ha_commands']:
            reply.update(ok=False, error='not_allowed')
            self.find('warning', 'questions', f'asked {ask!r}, which permissions.ha_commands does not name: the app refuses it')
        elif os.environ.get('TESSERA_HA_URL') and os.environ.get('TESSERA_HA_TOKEN'):
            try:
                result = await live_ha_service(os.environ['TESSERA_HA_URL'], os.environ['TESSERA_HA_TOKEN'], ask, body.get('data') or {})
                reply.update(ok=True, result=answer_of(self.entry, ask, result, self.spec.get('time_zone') or ZONE))
            except Exception as error:
                reply.update(ok=False, error='ha_preview_failed')
                self.find('warning', 'questions', f'live Home Assistant call {ask!r} failed: {str(error)[:220]}')
        elif ask not in commands:
            reply.update(ok=False, error='no answer in preview.yaml')
            self.find('info', 'questions', f'asked {ask!r}; preview.yaml has no answer under commands, so it got none')
        else:
            result = moments(commands[ask], self.spec.get('time_zone') or ZONE, self.now)
            reply.update(ok=True, result=answer_of(self.entry, ask, result, self.spec.get('time_zone') or ZONE))
'''
    if old not in source:
        fail("cannot find the expected service-answer block in bench.py; upstream code has changed")
    source = source.replace(old, new, 1)
    bench.write_text(source, encoding="utf-8")
    print(f"Temporarily patched local Preview Bench: {bench}")
    return bench, source


def main() -> int:
    if not os.environ.get("TESSERA_HA_URL") or not os.environ.get("TESSERA_HA_TOKEN"):
        fail("set TESSERA_HA_URL and TESSERA_HA_TOKEN before running")
    if not os.environ.get("TESSERA_MEALIE_CONFIG_ENTRY_ID"):
        fail("set TESSERA_MEALIE_CONFIG_ENTRY_ID to the Mealie integration entry ID from Home Assistant")
    if not os.environ["TESSERA_HA_URL"].startswith(("http://", "https://")):
        fail("TESSERA_HA_URL must start with http:// or https://")

    plugin_root = Path(__file__).resolve().parents[1]
    preview_repo = Path(os.environ.get("TESSERA_PLUGINS_DIR", plugin_root.parent / "tessera-plugins")).expanduser()
    preview_script = preview_repo / "tools" / "preview.py"
    if not preview_script.is_file():
        fail(f"cannot find {preview_script}; set TESSERA_PLUGINS_DIR to your tessera-plugins checkout")

    if not (TREE / "tools" / "render" / "host.py").is_file():
        TREE.parent.mkdir(parents=True, exist_ok=True)
        if TREE.exists():
            shutil.rmtree(TREE)
        print(f"Cloning official Tessera firmware tools into {TREE} ...")
        subprocess.run(["git", "clone", "--depth", "1", REPOSITORY, str(TREE)], check=True)
    patched_bench, original_bench = patch_bench(preview_repo)

    env = os.environ.copy()
    env["TESSERA_TREE"] = str(TREE)
    plugin_config = plugin_root / "plugin.yaml"
    original_config = plugin_config.read_text(encoding="utf-8")
    marker = '  CONFIG_ENTRY_ID: ""'
    replacement = '  CONFIG_ENTRY_ID: "' + env["TESSERA_MEALIE_CONFIG_ENTRY_ID"].replace('"', '') + '"'
    if marker not in original_config:
        fail(f"cannot find the empty CONFIG_ENTRY_ID default in {plugin_config}")
    plugin_config.write_text(original_config.replace(marker, replacement, 1), encoding="utf-8")
    command = [sys.executable, str(preview_script), str(plugin_root), *sys.argv[1:]]
    print("Starting Tessera Preview Bench with live Home Assistant service calls ...")
    try:
        return subprocess.run(command, env=env).returncode
    finally:
        plugin_config.write_text(original_config, encoding="utf-8")
        patched_bench.write_text(original_bench, encoding="utf-8")
        print("Restored plugin.yaml and the original Preview Bench; no local credentials or entry IDs were saved.")


if __name__ == "__main__":
    raise SystemExit(main())
