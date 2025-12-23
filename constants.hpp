// Copyright 2025 Piotr Gdanski
// Licensed under the MIT License.
 

#pragma once
#include <vector>
#include <unordered_set>
#include <string>

struct score_assigment{
    std::string property{};
    int score{};
};

/// A list of forbidden words that should be excluded from the search.
const std::vector<std::string> BLACKLIST = {
    // Category 1 - damage
    "uszkodzony",
    "uszkodzone",
    "uszkodzona",
    "pekniety",
    "peknieta",
    "pekniete",
    "zlamany",
    "zlamana",
    "zlamane",
    "rozklejony",
    "rozklejona",
    "delaminacja",
    "naprawiany",
    "naprawiana",
    "klejony",
    "zniszczony",
    "zniszczona",
    "zdekompletowane",
    "zdezelowane",
    "dziura",
    "wyrwana",
    "krawedz",
    // Category 2 - products other than skis
    "kurtka",
    "spodnie",
    "rekawice",
    "rekawiczki",
    "kombinezon",
    "bielizna",
    "skarpety",
    "pokrowiec",
    "rzepy",
    "bagaznik",
    "uchwyt",
    "belki",
    "boks",
    "thule",
    // Category 3 - service/activites offfer instead of skis
    "wypozyczalnia",
    "wypozyczenie",
    "ostrzenie",
    "smarowanie",
    "regeneracja",
    "montaz",
    "regulacja",
    "instruktor",
    "szkolenie",
    "lekcje",
    "wyjazd",
    "transport",
    // Category 4 snowboard and running skis
    "snowboard",
    "deska",
    "biegowe",
    // Category 5 - kids equipment
    "dzieciece",
    "junior",
    "juniorskie",
    "male",
    "dziecko",
};

/// A list of required words (brands) that should be prioritized in the search.
const std::vector<std::string> WHITELIST = {
    "atomic",
    "salomon",
    "fischer",
    "head",
    "rossignol",
    "volkl",   
    "blizzard",
    "nordica",
    "elan",
    "dynastar",
    "armada",
    "faction",
    "line",
    "majesty",     
    "blackcrows",  
    "dynafit",
    "skitrab",     
    "blackdiamond",
    "k2",
    "dps",
};

// TODO: Add more models 
///A list of word-score pairs used to assign scores to tokens based on their relevance.
const std::vector<score_assigment> SCORE{
    // Premium models
        // Atomic
        {"redster", 30},
        {"backland", 20},
        {"bent", 40},
        // Salomon
        {"qst", 50},
        {"srace", 40},
        // Fisher
        {"rc4", 20},
        // Volkl
        {"racetiger", 30},
        // Head
        {"rebels", 50},
        // Faction
        {"prodigy", 40},

    // Extra properties
        {"sl", 10},
        {"gs", 10},
        {"fis", 30},
        {"master", 20},
        {"race", 5},    
        {"ti", 5},
        {"freeride", 20},
        {"skitour", 10},
        {"nowe", 15}

};