#pragma once
#include<string>

#include "../Config/config.hpp"
#include "../Category/category.hpp"

void buildHome(Config *conf, Category *categories[], int categories_length, std::string path);
