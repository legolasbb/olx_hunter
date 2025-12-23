cmake_minimum_required(VERSION 4.2.1)

project(OlxScraper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -O3)

set(SOURCES
    main.cpp
    analyze_offer.cpp
    utils.cpp
)

set(HEADERS
    analyze_offer.hpp
    utils.hpp
    constants.hpp
    nlohmann/json.hpp
)

add_executable(olx_analyser ${SOURCES} ${HEADERS})
target_include_directories(olx_analyser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})