// Copyright 2025 Piotr Gdanski
// Licensed under the MIT License.

#pragma once
#include <string_view>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>

#include "utils.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int safe_price(const json offer){
    const auto price {offer["price"]};

    if(price.is_number()){
        return price.get<int>();
    } 

    if(price.is_string()){
        std::string s {price.get<std::string>()};
        std::replace(s.begin(), s.end(), ',', '.');

        try {
            return static_cast<int>(std::stod(s));
        }
        catch (...){
            return 0;
        }
    }
}

int levenshtein(std::string_view a, std::string_view b){
    int n {static_cast<int>(a.size())};
    int m {static_cast<int>(b.size())};
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

    // Changing any string of size i can be done in no less than i opertions (i deletions)
    for(int i = 0; i <= n; i++) dp[i][0] = i;
    for(int j = 0; j <= m; j++) dp[0][j] = j;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(a[i-1]==b[j-1]){
                // Characters are the same, no need to change
                dp[i][j]=dp[i-1][j-1];
            }
            else{
                // Choosing lowest cost option (insertion, deletion, or substitution)
                dp[i][j]=std::min(dp[i-1][j-1], std::min(dp[i-1][j], dp[i][j-1]))+1;
            }
        }
    }

    return dp[n][m];
}

std::string clean_string(std::string s){
    std::string clean_s {""};
    for(char x: s){
        if(isalnum(x)){
            clean_s+=x;
        }
    }
    return clean_s;
}

std::vector<std::string>tokenize(std::string s){
    
    std::vector<std::string>tokens;
    std::stringstream ss(s);
    std::string buffer{};

    while(ss >> buffer){
        tokens.push_back(clean_string(buffer));        
    }
    return tokens;
}

bool is_offer(const int price, const int score){
    if(score<10 || price < 100){
        return false;
    }
    constexpr int base_price = 100;
    constexpr int price_for_point = 15;

    const int max_price = base_price + price_for_point*score;
    
    if(price>max_price){
        return false;
    }
    return true;
}