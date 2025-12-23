// Copyright 2025 Piotr Gdanski
// Licensed under the MIT License.

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "nlohmann/json.hpp"
#include "analyze_offer.hpp"
#include "utils.hpp"

using json = nlohmann::json;

struct offer_ratio
{
    int score{};
    int price{};
    std::string link;
};

bool compare(const offer_ratio& a, const offer_ratio& b){
    // price1 / score1 > price2 / score2
    return a.price*b.score < b.price * a.score; 
}


std::vector<offer_ratio>best_offers(){
    std::vector<offer_ratio>links;
    std::ifstream f("ski_data.json");
    json data = json::parse(f);
    
    for(auto offer: data){
        std::string title {offer["title"]};
        std::string link {offer["link"]};
        std::string price_str {offer["price"]};
        int price {safe_price(offer)};
        int score {offer_score(title)};
        // TODO: is_offer does not work
        if(is_offer(price, score)){
            offer_ratio temp{};
            temp.price = price;
            temp.score = score;
            temp.link = link;
            links.push_back(temp);
        }
    }

    std::sort(links.begin(), links.end(), compare);

    return links;
}

int main(){
    
    constexpr int offers_number{100};
    int i =0;
    for(const auto x: best_offers()){
        if(i>=offers_number){
            break;
        }
        std::ofstream outfile("offers.txt", std::ios::app);
        if (outfile.is_open()) {
            outfile << "olx.pl" << x.link << "\n";
            outfile.close();
        } else {
            std::cerr << "Error: Unable to open file for writing.\n";
        }
        i++;
    }    
}
