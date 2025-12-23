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
For example in Polish words "uszkodzone" and "uszkodzona" have almost the same meaing (damaged). 
Normal words comparing would consider these words different, thus we use levenshtein distance.
## Adjusting constants for other product categiories
Adjusting for other categorie can be done without almost any coding knowledge and understanding of offer finding system. Only this needed is changing constants in blaclist, whitelist and scoring. 
- In blaclist you should put all words that would make offer not attractive for you. For phones it could be "pekniety" (cracked), "zablokowany" (locked) etc. 
It is good idea to also filter offers that are not phones, for example phone service/exchange
- Whitelist should contain all words that will allow you to filter trash/low quality offers. For phones category you could put brand names there (apple, samsung, ...0
- Scoring should contain all atributes that increase value of product. For example in phones category - models (17 - for iphones, galaxy - for samsung), memory (256gb, 512gb), and other model attributes (pro, max, mini). You can experiment with scores that you assign for attributes, so you get best results.
You may also need to alter base_price and price_for_point constants since in different categories max prices will differ.
- Last thing that needs to be adjusted is url in scrapper.py. You should change it to link to desirable category in Olx.
  
After this changes offer finder should work for any category.
## How to run
### Prerequisites
- **C++ compiler** (GCC/Clang) supporting C++17
- **CMake** (Version 4.2.1+)
- **Python** (Version 3.8+)

### Installation and build
### Python enviroment setup
It is highly recommended to use virtual enviroment.
```bash
  # Create virtual enviroment
  python3 -m venv venv

  # Activate virtual enviroment
  source /venv/bin activate

  # Install required packages
  pip3 install -r requirements.txt
```
### C++ listings analyser build
```bash
  #Create build directory
  mkdir -p build

  #set location of CMakeLists.txt file
  cd build
  cmake ..

  #Build project
  make

  #return to main directory
  cd ..
```
### Running scrapper and listings analyzer
```bash
  # Run scraper
  # Disclaimer:
  # This script is intended for research and educational purposes only. Always respect the website's robots.txt and terms of service. Unauthorized scraping may violate the website's policies.
  python3 scraper.py

  # Runnging listing analyser
  ./build/olx_analyser
```
After all steps links to best listings will be saved in offers.txt file.
