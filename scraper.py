#Copyright 2025 Piotr Gdanski
#Licensed under the MIT License.

"""
scraper.py - OLX Scraper

Description:
This script scrapes ski-related offers from the OLX website. It collects data such as the title, price, and link for each offer and saves the results in a JSON file.

Disclaimer:
This script is intended for research and educational purposes only. Always respect the website's robots.txt and terms of service. Unauthorized scraping may violate the website's policies.

Last Updated:
13.12.2025
"""

import requests, bs4, time, random, json, unidecode

# Setting custom headers to mimic a real browser
HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
}

# Defining the base URL for ski offers and number of pages to scrape
SEARCH_URL = "https://www.olx.pl/sport-hobby/sporty-zimowe/narty/"
PAGE_NUM = 20

ski_data = []

for page in range(1, PAGE_NUM + 1):
    print(f"Getting page {page}/{PAGE_NUM}")
    # Random sleep (from 1 to 5 seconds) so the server is not overloaded
    stop = random.randint(1, 5)
    time.sleep(stop)
    
    url = SEARCH_URL + "?page=" + str(page)

    r = requests.get(url)

    if r.status_code == 200:
        # If succesful parse the page
        soup = bs4.BeautifulSoup(r.text, "html.parser")

        # Finding all divs containg offers
        items = soup.find_all("div", attrs={"data-cy": "ad-card-title"})
        
        # Extracting data from each offer
        for item in items:
            title = item.h4
            if title != None:
                # Extracting title text and converting it to lowercase, geting rid of polish characters
                title_text = str(title.contents)
                title_text = title_text[2:len(title_text)-2]
                title_text = unidecode.unidecode(title_text).lower()
            
            # Finding price element and extracting price text
            price = item.find("p", attrs={"data-testid": "ad-price"})
            end =0
            price_text=str(price.contents)
            while price_text[end]!="z":
                end+=1
            price_text = price_text[2:end-1]

            # Finding link element and extracting link text
            link_tag = item.a
            lint_text = link_tag["href"]

            # Appending extracted data to the list as dictionary
            ski_data.append({
                "title": title_text,
                "price": price_text,
                "link": lint_text
            })
    else:
        # If request was not successful, break the loop
        break

# Saving all data to a json file
with open("ski_data.json", "w") as f:
    json.dump(ski_data, f, ensure_ascii=False, indent=4)