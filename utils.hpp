// Copyright 2025 Piotr Gdanski
// Licensed under the MIT License.

#include <string_view>
#include <string>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

/// Calculates the Levenshtein distance between two strings, which is a measure of 
/// the minimum number of single-character edits (insertions, deletions, or substitutions) 
/// required to change one string into the other.
/// 
/// @param a The first input string to compare.
/// @param b The second input string to compare.
/// @return The Levenshtein distance between the two strings.
int levenshtein(std::string_view a, std::string_view b);

/// Cleans a string by removing non-alphanumeric characters.
/// 
/// @param s The input string to clean.
/// @return A cleaned version of the input string with only alphanumeric characters.
std::string clean_string(std::string s);

/// Splits a string into tokens (words) by whitespace, removing non-alphanumeric characters 
/// from each token in the process.
/// 
/// @param s The input string to tokenize.
/// @return A vector of cleaned tokens extracted from the input string.
std::vector<std::string>tokenize(std::string s);

/// Extracts and converts the price from a JSON offer object.
/// Handles both numeric and string representations of the price.
/// Returns 0 if the price is invalid or cannot be parsed.
///
/// @param offer A JSON object containing the offer details.
/// @return The extracted price as an integer.
int safe_price(const json offer);

/// Linear heuristic checking if product is an a good offer.
/// Produt is an offer when price <= base_price + points * price_for_point
/// base_price and price_for_point are constants that can be adjusted for best results
///
/// @param price Price of the product
/// @param score Score of the product (points)
/// @return boolean value, stating if product is an offer
bool is_offer(const int price, const int score);

