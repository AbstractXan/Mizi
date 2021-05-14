#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/template.hpp"
#include "../include/helpers.hpp"

using namespace std;

TemplateManager::TemplateManager(std::string templateFile)
{
    this->tmap = new TemplateMap;
    this->templateCreatorParser(templateFile);
}
/**
 * Parses templatefile and stores in tmap
 */
void TemplateManager::templateCreatorParser(std::string templatefile)
{
    Template *currTemplate = nullptr;
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
                    currTemplate = nullptr;
                    break;
                }
                else if (isParsingTemplate)
                {
                    parseAndSaveTemplateContent(currTemplate, line);
                }
                i++;
            }
        }
        templateFile.close();
    }
    else
    {
        cout << "[!] Provided template file not found in given path [!]" << endl;
    }
}

// Input {{template arg1=value1 arg2=value2}}
// template arg1 value1 arg2 value2
std::string TemplateManager::templateReaderParser(std::string templateText)
{
    // Get template name and args
    // std::string test_output = "";
    vector<string> tokens = tokenizer(templateText, "= ");
    // for(auto str: tokens){
    //     test_output+= str + " ";
    // }
    // if(!test_output.empty())
    //     test_output.pop_back();

    std::string templateName = tokens[0];

    //TODO: verify template name
    //TODO: verify arg names and numbers
    //if (!VerifyTemplateHeaders(tokens))
    // return "";

    auto argValMap = this->generateTemplateArgValueMap(tokens);
    // Use this map to replace args;
    //return test_output;

    return "";
}
string TemplateManager::templateRenderer()
{
    return "hello";
}

std::unordered_map<std::string, std::string> *TemplateManager::generateTemplateArgValueMap(std::vector<std::string> args)
{

    std::unordered_map<std::string, std::string> *argValMap = new std::unordered_map<std::string, std::string>;

    // i=0 has templateName
    for (size_t i = 1; i < args.size(); i++)
    {
        if (i % 2 == 0)
        {
            argValMap->insert(std::make_pair(args[i - 1], args[i]));
        }
    }
    return argValMap;
}
/**
 * Parses a line inside template body in template.txt
 * Saves parsed text and args into the template
 * 
 * @param template_ptr 
 * @param TemplateText
 * @return void
 */
void parseAndSaveTemplateContent(Template *template_ptr, std::string content)
{
    size_t i = 0, lineSize = content.size();

    // For content "<p> text <p>"
    // text = [ "<p> text <p>" ]
    // arg = [ ]

    // For content "<p> $$var$$ <p>"
    // text = [ "<p> " , " <p>" ]
    // arg = [ "var" ]

    // For content "$$var$$ boop!"
    // text = [ "" , " boop!" ]
    // arg = [ "var" ]

    // variables are case sensitive
    // it is recommended to not use spacing when using variables:
    // $$ var $$ will give " var " as variable name and will not be the same as "var"

    std::string text = "";

    while (i < lineSize)
    {
        // If not an arg and we see '$$'
        if (i + 1 < lineSize && content[i] == '$' && content[i + 1] == '$')
        {
            i += 2;
            bool argParseSuccessful = false;
            bool hasSpace = false;

            // Parse through arg
            string arg = "";
            while (i < lineSize && content[i] != '$')
            {
                if (content[i] == ' ')
                {
                    hasSpace = true;
                    break;
                }
                arg += content[i];
                i++;
            }

            //Complete parsing an arg when we see '$$' at the end
            argParseSuccessful = !hasSpace && (i + 1 < lineSize && content[i] == '$' && content[i + 1] == '$');

            if (argParseSuccessful && arg != "")
            {
                // cout << "SAVING TEXT: '" << text << "'" << endl;
                template_ptr->text.push_back(text);
                text = "";

                // cout << "SAVING ARG: '" << arg << "'" << endl;
                template_ptr->args.push_back(arg);

                i += 2;
            }
            else
            {   // Append to text if not successful
                // cout << "WRONG ARG PARSE: '" << arg << "'" << endl;
                text += "$$" + arg;
            }
        }
        else
        {
            text += content[i];
            i++;
        }
    }
    template_ptr->text.push_back(text);
}