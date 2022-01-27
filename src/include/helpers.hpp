#pragma once
#include <string>
#include <fstream>
#include "template.hpp"
#include "config.hpp"

char getLower(char c);
std::string toLowerCase(std::string text);
void printError(int linenumber, std::string text);

std::vector<std::string> tokenizer(const std::string, const std::string &);

std::string parseLinks(std::string text, std::string path, TemplateManager *);
std::string printVector(std::vector<std::string> vec);


void checkProjectFileStructure(Config *conf);
void createFileIfDNE(std::string path, std::string defaultData);