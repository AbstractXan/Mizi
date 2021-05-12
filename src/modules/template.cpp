#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/template.hpp"
#include "../include/helpers.hpp"

using namespace std;

TemplateManager::TemplateManager(std::string templateFile){
    this->templateCreatorParser(templateFile);
}
/**
 * Parses templatefile and stores in tmap
 */
void TemplateManager::templateCreatorParser(std::string templatefile)
{
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

            // if @@ => start/end of template
            bool isTemplateStartOrEnd = (line[i] == '@' && line[i + 1] == '@');
            
            // Parse line
            while (i < line.size())
            {
                
                // start of template
                if (isTemplateStartOrEnd && !isParsingTemplate)
                {
                    i += 2;
                    // create template
                    currTemplate = new Template;
                    vector<string> tokens = tokenizer(line.substr(i, line.size() - i + 1), "@(,)");

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
                    // Store in Template map of Template Manager
                    this->tmap->insert(pair<std::string, Template *>(currTemplate->name, currTemplate));
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
}

std::string TemplateManager::templateReaderParser(std::string){
    return "hello";
}
string TemplateManager::templateRenderer()
{
    return "hello";
}