# Development plan

The goal is an installable Tessera recipe browser for large 1280 × 800 touch displays. A separate Lovelace card is not part of the project.

The agreed target behavior and handoff rules are in [implementation-plan.md](implementation-plan.md).

## Phase 0 – Foundations
- [x] GitHub repository created
- [x] Mealie data model reviewed
- [x] Tessera selected as the only frontend
- [x] Large-display targets selected
- [x] Official Tessera board IDs checked
- [x] Plugin API 0.28 and official manifest schema reviewed
- [x] Plugin skeleton and full-screen tile created

## Phase 1 – Home Assistant bridge
- [x] Existing Home Assistant Mealie integration reused
- [x] Separate short bridge bearer key
- [x] Paginated recipe list endpoint (five recipes per request)
- [x] On-demand recipe detail endpoint
- [x] Bridge category endpoint added (live verification pending)
- [x] Bridge search and category parameters added (live verification pending)
- [x] Preserve pagination metadata in bridge response (live verification pending)
- [ ] Verify category endpoint against installed Mealie version
- [ ] Verify search and category filters against installed Mealie version
- [ ] Verify exact pagination response and last-page behavior
- [ ] Test invalid key, missing Mealie entry and Mealie errors

## Phase 2 – Tessera data path
- [ ] Replace direct Mealie requests with bridge requests
- [ ] Remove Mealie API token input from the target plugin setup
- [ ] Add bridge URL and bridge key configuration using supported Tessera mechanisms
- [ ] Map recipe summary and pagination metadata
- [ ] Load categories dynamically
- [ ] Load full recipe details on demand
- [ ] Preserve structured ingredient data in detail responses

## Phase 3 – Recipe browser UI
- [x] Initial full-screen recipe tile
- [x] Initial three-column grid foundation
- [ ] Header across full display width
- [ ] Left navigation sidebar
- [ ] Search field and on-screen keyboard
- [ ] Dynamic category list and “Alle Rezepte”
- [ ] Search and category can be combined
- [ ] 3×8 recipe grid for up to 24 results
- [ ] Collect five-item bridge responses into a 24-item buffer
- [ ] Pagination controls and total-page indicator
- [ ] Keep active filters when moving between displayed pages
- [ ] Reset to first page when a filter changes
- [ ] Loading, empty and error states
- [ ] Prevent stale responses from an older filter state

## Phase 4 – Cooking features
- [ ] Adjust serving count using structured ingredient quantities
- [ ] Check off ingredients
- [ ] Step-by-step cooking view
- [ ] Previous/next step
- [ ] Optional timer

## Phase 5 – Preview, testing and release
- [x] Official Tessera plugin checker workflow configured
- [ ] Official Preview Bench succeeds for enabled large displays
- [ ] Check layout and readability at target resolutions
- [ ] Generate `store.png` from a clean Preview Bench run
- [ ] Install the plugin on a test screen
- [ ] Test touch interaction, memory use and response sizes
- [ ] Test on Guition JC8012P4A1C-I-W-Y / hardware V3

## Development rules

- Keep commits small and reviewable.
- Verify API paths, parameters and response fields against the installed Mealie instance.
- Read [implementation-plan.md](implementation-plan.md) before beginning work.
- Use the Home Assistant bridge; do not reintroduce a Mealie API token in Tessera.
- Never commit secrets, API tokens or other credentials.
- Do not overwrite existing Home Assistant or Tessera configuration without explicit instruction.
