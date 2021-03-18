#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/template.hpp"
#include "../include/helpers.hpp"

using namespace std;

/** 
 * Tokenizes based on delims
 */
vector<string> split(const std::string &str, const std::string &delims = " ")
{
    vector<string> tokens;
    std::size_t nextIndex, currIndex = 0;
    // Find next instance of delim
    nextIndex = str.find_first_of(delims);
    // While delims exist
    while (nextIndex != std::string::npos)
    {
        // Add token
        tokens.push_back(str.substr(currIndex, nextIndex - currIndex));
        currIndex = nextIndex + 1;
        nextIndex = str.find_first_of(delims, currIndex);
    }
    // Push last string chunk
    if (currIndex < str.size()){
        tokens.push_back(str.substr(currIndex, str.size() - currIndex));
    }
    return tokens;
}

/**
 * Parses templatefile
 */
TemplateMap *templateParser(string templatefile)
{
    TemplateMap *tmap = new TemplateMap;

    Template *currTemplate;
    bool isParsingTemplate = false;

    ifstream templateFile(templatefile);
    if (templateFile.is_open())
    {
        string line;
        while (getline(templateFile, line))
        {
            size_t i = 0;

            if (line.size() < 1)
                continue; //blanks

            // Parse line
            while (i < line.size())
            {
                // if @@ => start/end of template
                bool isTemplateStartOrEnd = (line[i] == '@' && line[i + 1] == '@');
                // start of template
                if (isTemplateStartOrEnd && !isParsingTemplate)
                {
                    i += 2;
                    // create template
                    currTemplate = new Template;
                    vector<string> tokens = split(line.substr(i, line.size() - i + 1), "@(,)");

                    // Assign temporarily
                    currTemplate->name = tokens[0];
                    tokens.erase(tokens.begin()); // Remove name from args;
                    currTemplate->args = tokens;

                    isParsingTemplate = true;
                    break;
                } 
                // If faces '@@' and  already parsing -> end and save template
                else if (isTemplateStartOrEnd && isParsingTemplate)
                {
                    tmap->insert(pair<std::string, Template *>(currTemplate->name, currTemplate));
                    isParsingTemplate = false;
                    break;
                }
                else if (isParsingTemplate)
                {
                    
                }
                i++;
            }
        }
        templateFile.close();
    }
    return tmap;
}

string templateRederer()
{
}