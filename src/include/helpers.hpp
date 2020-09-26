#pragma once
#include <string>

char getLower(char c);
std::string toLowerCase(std::string text);
void printError(int linenumber,std::string text);
std::string parseLinks(std::string text, std::string path);