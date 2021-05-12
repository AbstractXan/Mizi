#pragma once

#include<iostream>
#include<string>
#include "page.hpp"
#include "template.hpp"

struct Category
{
    std::string name;
    int pageCount;
    Page * pages[32];
};

Category *createCategory(Category *Categories[16], std::string name, int count);
Category **createCategories(Category *Categories[16], int *categoryCount, std::string filename, std::string path, TemplateManager* TemplateMgr);
void addPage(Category *category, Page *page);
void printContent(Category *cats[], int count);
