# Architecture

## Goal

A Tessera recipe browser for the large 10.1-inch kitchen display. It adds a dedicated recipe view without replacing the existing Tessera dashboard.

## Data path

```text
        Mealie v3 REST API
       https://luigi.mahlen.biz
                 |
       HTTPS + bearer API token
                 |
          Tessera app fetcher
          /              \
   recipes page 1..5    recipe detail
   5 items per page    one slug per ask
          \              /
           mapped compact JSON
                  |
        Tessera plugin firmware
                  |
       24-card recipe grid / detail
```

The screen firmware never opens a network connection. The Tessera app performs the HTTPS requests, keeps the API token in its secret storage and sends only the mapped fields to the screen.

## Responsibilities

### Mealie
- Source of recipe summaries, categories, ingredients and preparation steps.
- Provides pagination through `GET /api/recipes?page=<page>&perPage=5`.
- Provides recipe details through `GET /api/recipes/{slug}`.

### Tessera app
- Stores the API token as a secret input.
- Sends the bearer token only to the declared Mealie hostname.
- Fetches five recipe pages and maps each response to compact fields.
- Fetches one recipe's detail response when the screen asks for it.

### Tessera plugin
- Requests pages 1 through 5 and combines up to 24 recipes.
- Shows the results in a three-column, eight-row full-screen grid.
- Opens the detail card for the tapped recipe.
- Displays up to six ingredients and three preparation steps.

## Current implementation

1. The full-screen tile sends five `fetch:recipes` requests, one for each page.
2. Each page contains at most five compact recipe summaries.
3. The plugin collects the replies and retains up to 24 recipes.
4. A tap opens the detail card and sends `fetch:recipe` with the recipe slug.
5. The app maps the detail response to the fields the card displays.

The Mealie hostname is fixed in the manifest because Tessera requires fetch hosts to be explicitly allowlisted and does not permit a user-supplied host in the URL.

## Technical constraints

- Target resolution: 1280 × 800 pixels.
- The browser tile takes the whole page.
- Plugin API 0.28.
- API token is a Tessera secret input and must never be committed.
- Each mapped text field is limited to 48 bytes; long ingredient and instruction text can be shortened.
- The screen receives only the mapped result, not the full Mealie response.

## Later work

- Search and category filters.
- More than six ingredients and three instructions through segmented detail requests.
- Cooking mode, ingredient checklist and step navigation.
- Live and physical-screen verification.
