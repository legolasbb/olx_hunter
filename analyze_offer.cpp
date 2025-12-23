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
#include <fstream>
#include <cmath>

#include "constants.hpp"
#include "utils.hpp"

/// @brief Determines if two tokens are similar based on their Levenshtein distance.
/// 
/// The function compares two tokens and checks if their Levenshtein distance is within
/// an acceptable threshold. The threshold is determined based on the length of the tokens.
/// 
/// @param token1 The first token to compare.
/// @param token2 The second token to compare.
/// @return true If the tokens are considered similar.
/// @return false If the tokens are not similar.
bool is_token_similar(std::string token1, std::string token2);

/// @brief Checks if a given token is blacklisted.
/// 
/// A token is considered blacklisted if it is similar to any token in the predefined blacklist.
/// 
/// @param token The token to check.
/// @return true If the token is blacklisted.
/// @return false If the token is not blacklisted.
bool is_blacklisted(std::string token);

/// @brief Checks if a given token is whitelisted.
/// 
/// A token is considered whitelisted if it is similar to any token in the predefined whitelist.
/// 
/// @param token The token to check.
/// @return true If the token is whitelisted.
/// @return false If the token is not whitelisted.
bool is_whitelisted(std::string token);

/// @brief Calculates the score of a given token based on predefined scoring rules.
/// 
/// The score is determined by comparing the token to a list of properties with associated scores.
/// 
/// @param token The token to score.
/// @return int The calculated score for the token.
int token_score(std::string token);




bool is_token_similar(std::string token1, std::string token2){
    if(std::abs(static_cast<int>(token1.size()) - static_cast<int>(token2.size())) > 3){
        return false;
    }
    int distance {levenshtein(token1, token2)};

    if(std::max(token1.size(), token2.size())>4 && distance<=2){
        return true;
    }
    else if(std::max(token1.size(), token2.size())<=4 && distance<=1){
        return true;
    }
    return false;
}

bool is_blacklisted(std::string token){
    for(auto blacklisted_token: BLACKLIST){
        if(is_token_similar(token, blacklisted_token)){
            return true;
        }
    }
    return false;    
}

bool is_whitelisted(std::string token){
    for(auto whitelisted_token: WHITELIST){
        if(is_token_similar(token, whitelisted_token)){
            return true;
        }
    }
    return false;   
}

int token_score(std::string token){
    int score{0};
    for(auto token_score: SCORE){
        if(is_token_similar(token, token_score.property)){
            score+=token_score.score;
        }
    }
    return score;
}

int offer_score(std::string offer){
    std::vector<std::string>offer_tokens;
    for(const auto token: tokenize(offer)){
        // Geting rid of conjunctions
        if(token.size()>1){
            offer_tokens.push_back(token);
        }
    }

    for(const auto token: offer_tokens){
        if(is_blacklisted(token)){
            return 0;
        }
    }

    bool whitelisted {false};

    for(const auto token: offer_tokens){
        if(is_whitelisted(token)){
            whitelisted=true;
            break;
        }
    }

    if(!whitelisted){
        // If no words are whitlisted (known brands), offer is rejected
        return 0;
    }

    int score{0};
    
    for(const auto token: offer_tokens){
        score+=token_score(token);
    }

    return score;
}

