# Live Mealie API preview

The official Tessera Preview Bench can call the same Mealie API fetches used by the installed plugin. No Home Assistant service bridge or Mealie config-entry ID is needed.

## Requirements

- The official `tessera-plugins` repository checked out next to this repository, unless `TESSERA_PLUGINS_DIR` is set.
- The Preview Bench set up once (`python3 tools/preview.py --setup` in the official checkout).
- A long-lived Mealie API token.
- Network access from the preview environment to `https://luigi.mahlen.biz`.

## Run from WSL

Set the token in the environment. Do not put it in a source file or commit it:

```bash
export TESSERA_SECRET_API_TOKEN="YOUR_MEALIE_API_TOKEN"
python3 tools/preview.py ../mealie-tessera-plugin --board jc8012p4a1v3 --live --window
```

The exact command assumes the current directory is the official `tessera-plugins` checkout and this repository is its sibling. Change the path or set `TESSERA_PLUGINS_DIR` if your checkouts are elsewhere.

For a fixture-only preview, omit `--live`; the sample data in `preview.yaml` supplies all five recipe pages and the detail response.

## What it does

- Uses the manifest's `recipes` fetch five times, with page values 1 through 5.
- Uses the manifest's `recipe` fetch when the first preview recipe is opened.
- Sends the token as a bearer token over HTTPS to the host declared in `permissions.network`.
- Keeps the token out of the preview fixtures and repository.

## Security

Treat the Mealie token as a password. Do not share it in chat, screenshots, shell history, source files or Git. Environment variables are inherited by the preview process; unset the variable when finished:

```bash
unset TESSERA_SECRET_API_TOKEN
```

Revoke the token in Mealie when it is no longer needed.

## Limitations

This is a local development preview, not a physical-screen test. It depends on the official Preview Bench and the Mealie host being reachable from WSL/Linux. The plugin manifest currently names `luigi.mahlen.biz`; a different Mealie host requires updating the manifest's network permission and fetch URLs.
