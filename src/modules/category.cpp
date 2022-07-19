#include <iostream>
#include <string>
#include <fstream>

#include "../include/page.hpp"
#include "../include/helpers.hpp"
#include "../include/category.hpp"

using namespace std;

Category *createCategory(Category *Categories[16], string name, int count)
{
    Category *newCategory = new Category;
    newCategory->name = name;
    newCategory->pageCount = 0;
    Categories[count] = newCategory;
    return newCategory;
}

Category **createCategories(Category *Categories[16], int *categoryCount, string filename, string path, TemplateManager *TemplateMgr)
{

    string line;
    int lineNo = 0;

    Category *currentCategory;
    Page *currentPage = NULL;
    bool uList = false;
    string currentPartName = "";
    string currentPartDesc = "";

    // Category for separate pages
    Category *separateCategory = createCategory(Categories, "SeparatePages", 0);

    ifstream mdFile(filename);

    if (mdFile.is_open())
    {
        while (getline(mdFile, line))
        {
            lineNo++;
            int hashcount = 0;
            int i = 0;

            if (line == "")
            {
                currentPartDesc += "<br>";
                continue;
            }

            // All the magic happens here
            line = parseLinks(line, path, TemplateMgr);


            if (line.substr(i, 5) == "# $$$")
            {
                // Separate page
                currentCategory = separateCategory;
                uList = false;
                continue;
            }

            // Headings
            if (line[i] == '#')
            {
                while (line[i] == '#')
                {
                    hashcount++;
                    i++;
                }

                // Category
                if (hashcount == 1)
                {
                    (*categoryCount)++; // Categories stored from 1 onwards ,
                                        // categories[0] for separate pages
                    currentCategory = createCategory(Categories, line.substr(i + 1, line.size() - i),
                                                     *categoryCount);
                    uList = false;
                }

                // Page
                else if (hashcount == 2)
                {
                    if (currentCategory->name.empty())
                    {
                        printError(lineNo, "No Category assigned!");
                        return NULL;
                    }
                    currentPage = createPage(line.substr(i + 1, line.size() - i));
                    addPage(currentCategory, currentPage);
                    uList = false;
                }

                // Part
                else if (hashcount == 3)
                {
                    if (currentCategory->name.empty())
                    {
                        printError(lineNo, "No Category assigned!");
                        return NULL;
                    }
                    if (currentPage->title.empty())
                    {
                        printError(lineNo, "No Page assigned!");
                        return NULL;
                    }
                    // Current Part Name
                    currentPartName = line.substr(i + 1, line.size() - i);
                    addPart(currentPage, currentPartName);
                    currentPartDesc = "";
                    uList = false;
                }
            }
            else
            { // No headings: Plaintext

                // Ul
                if (line[i] == '-')
                {
                    i++;
                    // If not in a ul
                    if (uList == false)
                    {
                        currentPartDesc += "<ul>";
                        uList = true;
                    }

                    currentPartDesc += "<li>";
                    currentPartDesc += line.substr(i + 1, line.size() - i);
                    currentPartDesc += "</li>";
                }
                else
                { // If list doesn't continue
                    if (uList == true)
                    {
                        uList = false;
                        currentPartDesc += "</ul>";
                    }
                    currentPartDesc += "" + line + "<br>";
                }

                // For <ul> continuing to next part of the page, Every 'part name' has
                // an extra </ul> to keep a check. Refer to buildpage function

                // Update if page exists, add to current part i.e. (partsCount - 1)
                if (currentPage->title != "")
                    currentPage->partDesc[(currentPage->partsCount) - 1] = currentPartDesc;
            }
        }
        mdFile.close();
    }
    else
    {
        cout << "Unable to open file : " << filename << endl;
    }
    return Categories;
}

void addPage(Category *category, Page *page)
{
    category->pages[category->pageCount] = page;
    category->pageCount++;
}

// Debug
void printContent(Category *cats[], int count)
{
    for (int i = 0; i <= count; i++)
    {
        Category tempCat = *cats[i];
        cout << tempCat.name << endl;

        for (int pageno = 0; pageno < tempCat.pageCount; pageno++)
        {
            Page tempPage = *tempCat.pages[pageno];
            cout << "\t" << tempPage.title << endl;

            for (int partno = 0; partno < tempPage.partsCount; partno++)
            {
                cout << "\t\t |" << tempPage.partName[partno] << endl;
                cout << "\t\t |" << tempPage.partDesc[partno] << endl;
            }
        }
    }
}
