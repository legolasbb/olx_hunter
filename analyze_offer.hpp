// Copyright 2025 Piotr Gdanski
// Licensed under the MIT License.

#include <string>

/// @brief Calculates the overall score of an offer based on its tokens.
/// 
/// The function tokenizes the offer, checks for blacklisted and whitelisted tokens, 
/// and calculates the total score based on token scores. If any token is blacklisted 
/// or no token is whitelisted, the offer is rejected (score 0).
/// 
/// @param offer The offer text to evaluate.
/// @return int The calculated score for the offer.
int offer_score(std::string offer);
