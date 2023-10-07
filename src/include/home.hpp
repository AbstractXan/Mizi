#pragma once
#include<string>

#include "config.hpp"
#include "category.hpp"
#include "helpers.hpp"
std::string buildHome(Config *conf, Category *categories[], int categories_length, std::string path);
