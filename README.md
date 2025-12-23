# Olx Hunter
## What is Olx Hunter?
Olx hunter is offer analyzer/finder for olx (Polish online marketplice, similar to ebay/facebook marketplace). Currently functional for ski-related products, howevew it can be easily adjusted for other groups of products
## How does Olx Hunter work?
First product listings are scraped from Olx. Then every listing goes through analysis.
- **Scraping listing from Olx** 
- **Data preparation** - every title is cleared from non-alphanumeric characters, all leters are changed to lowercase, Polish characters are replaces with latin characters. Then data is saved to json file.
- **Blacklist** - All tokens are compared from words from blacklist. If any of the word is blacklisted, listing is rejected.
- **Whitelist** - Each of the lisings is required to have at least one token which appers on the whitelist. If none appear offer is rejected.
- **Scoring** - If listing goes through blacklist and whitelist check it is scored based on model, properties etc.
- **Offer linear heuristic** - each offer is compared with `max_price = base_price + score*price_per_point` , base_price and price_per_point are constants which can be adjusted for best results. If offers price is higher then max_price offer is rejected. Offers with very low score or price (likely trash or fake offers) are also rejected.
- **Sorting offers** - all remaing listing are sorted based on price to points ratio and links to listings are saved in text file
## Blaclist, Whitelist and Scoring
All of the comparisions and scoring is based on constants in constants.hpp file.
### Blacklist
Blacklist contains all words that disqualify listing for us. For example damaged or kids products
### Whitelist
Whitlist contains reputable brands names to help us discard low quality products
### Scoring 
Scoring contains pairs of product attributes and score assigned for the atribute. For example premium models, special technologies used.
### How words are compared?
Words are compared using levenshtein distance which allows to compare inflected words (with the same meaning) or ignore speling mistakes. 
For example in polish words "uszkodzone" and "uszkodzona" have almost the same meaing (damaged). 
Normal words comparing would consider these words different, thus we use levenshtein distance.
### Adjusting constants for other product categiories