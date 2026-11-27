# Development plan

The goal is an installable Tessera recipe browser for large touch displays from 7 inches. A separate Lovelace card is not part of the project.

## Phase 0 – Foundations
- [x] GitHub repository created
- [x] Mealie data model reviewed
- [x] Tessera selected as the only frontend
- [x] Large-display targets selected
- [x] Official Tessera board IDs checked
- [x] Plugin API 0.28 and official manifest schema reviewed
- [x] Plugin skeleton and full-screen tile created

## Phase 1 – Data path
- [x] Direct Mealie API access selected
- [x] Tessera secret input for the Mealie API token
- [x] Paginated recipe summary fetch (five pages of five)
- [x] Compact recipe summary mapping
- [x] On-demand recipe detail fetch by slug
- [x] Representative list and detail fixtures added
- [ ] Live Mealie fetch verified from the Preview Bench
- [ ] Actual list and detail response shapes verified against the installed Mealie version
- [ ] Long ingredient and instruction text handled through segmented loading
- [ ] Categories and search strategy implemented

## Phase 2 – Recipe browser
- [x] Full-screen recipe tile
- [x] Three-column grid for up to 24 recipes
- [x] Recipe name, time and servings
- [x] Tap a recipe to open details
- [x] Initial detail view with ingredients and preparation
- [ ] Search field and on-screen keyboard
- [ ] Category filter
- [ ] Recipe images and paging controls

## Phase 3 – Cooking features
- [ ] Adjust serving count
- [ ] Check off ingredients
- [ ] Step-by-step cooking view
- [ ] Previous/next step
- [ ] Optional timer

## Phase 4 – Preview, testing and release
- [x] Official Tessera plugin checker workflow configured
- [ ] Official Preview Bench succeeds for enabled large displays
- [ ] Check layout and readability at target resolutions
- [ ] Generate `store.png` from a clean Preview Bench run
- [ ] Install the plugin on a test screen
- [ ] Test touch interaction, memory use and response sizes
- [ ] Test on Guition JC8012P4A1C-I-W-Y / hardware V3

## Development rules

- Keep commits small and reviewable.
- Do not assume unverified Mealie response fields.
- Follow the official Tessera plugin structure and checks.
- Never commit secrets, API tokens or other credentials.
- Do not overwrite existing Home Assistant or Tessera configuration without explicit instruction.
