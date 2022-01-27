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
    if (templateFile == "")
        return;
    this->provisionTemplates(templateFile);
}
/**
 * Parses templatefile and stores templates in templatemap
 * @param templateFile path of templatefile
 * @return void
 */
void TemplateManager::provisionTemplates(std::string templatefile)
{
    Template *currTemplate = nullptr;
    bool isParsingTemplate = false;
    bool hasMultipleLines = false;
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
            }
            // If faces '@@' and  already parsing -> end and save template
            else if (isTemplateStartOrEnd && isParsingTemplate)
            {
                // Store in Template map of Template Manager
                this->tmap->insert(pair<std::string, Template *>(currTemplate->name, currTemplate));

                isParsingTemplate = false;
                currTemplate = nullptr;
                hasMultipleLines = false;
            }
            else if (isParsingTemplate)
            {

                //cout << "Parsing :  " << line << endl;
                parseAndSaveTemplateContent(currTemplate, line, hasMultipleLines);
                if (!hasMultipleLines)
                {
                    hasMultipleLines = true;
                }
            }
        }
        templateFile.close();
    }
    else
    {
        cout << "[!] Provided template file not found in given path [!]" << endl;
    }
}

/**
 * @brief Try to render template from given string
 * 
 * @param templateText String of format "template arg1=value1 arg2=value2"
 * @return String generated from template. If template, not found
 */
std::string TemplateManager::renderTemplateFromText(std::string templateText)
{
    vector<string> tokens = tokenizer(templateText, "= ");
    std::string templateName = tokens[0];
    auto argValMapPtr = generateTemplateArgValueMap(tokens);
    auto templatePtr = this->getTemplate(templateName);
    if (templatePtr)
    {
        return renderTemplate(templatePtr, argValMapPtr);
    }
    return "{{" + templateText + "}}";
}
/**
 * getter for Template reference
 * @param TemplateName
 * @return TemplatePtr or nullptr
 */
Template *TemplateManager::getTemplate(std::string templateName)
{
    auto tmapItr = this->tmap->find(templateName);
    if (tmapItr != this->tmap->end())
    {
        return tmapItr->second;
    }
    return nullptr;
}

std::unordered_map<std::string, std::string> *generateTemplateArgValueMap(std::vector<std::string> args)
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
 * @param template_ptr 
 * @param TemplateText
 * @param isMultiLine True when given line isn't the first line in template
 * @return void
 */
void parseAndSaveTemplateContent(Template *template_ptr, std::string content, bool isMultiLine = false)
{
    if (isMultiLine)
    {
        template_ptr->textContentList.push_back("<br>");
        template_ptr->argContentList.push_back("");
    }

    size_t i = 0, lineSize = content.size();

    std::string text = "";
    std::string arg = "";
    while (i < lineSize)
    {
        // If not an arg and we see '$$'
        if (i + 1 < lineSize && content[i] == '$' && content[i + 1] == '$')
        {
            i += 2;
            bool argParseSuccessful = false;
            bool hasSpace = false;

            // Parse through arg
            arg = "";
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
                // Push text then arg content
                template_ptr->textContentList.push_back(text);
                text = "";
                template_ptr->argContentList.push_back(arg);
                arg = "";
                i += 2;
            }
            else
            { // Append to text if not successful
                // cout << "WRONG ARG PARSE: '" << arg << "'" << endl;
                text += "$$" + arg;
                arg = "";
            }
        }
        else
        {
            text += content[i];
            i++;
        }
    }
    // Push text then arg content
    template_ptr->textContentList.push_back(text);
    template_ptr->argContentList.push_back(arg);
}

/**
 * @brief Render a template with given arguments and their values
 * 
 * @param template_ptr Pointer to template
 * @param argValMap Map of arguments and values from text
 * @return std::string 
 */
std::string renderTemplate(Template *template_ptr, std::unordered_map<std::string, std::string> *argValMap)
{
    std::string ret = "";
    // Alternatively render textChunks and argChunks
    // While replacing argChunks with corresponding value;
    for (size_t index = 0; index < template_ptr->textContentList.size(); index++)
    {

        //Debug: printVector(template_ptr->textContentList);
        //Debug: printVector(template_ptr->argContentList);

        ret += template_ptr->textContentList[index];

        if (index < template_ptr->argContentList.size())
        {
            auto argValueMapPtr = argValMap->find(template_ptr->argContentList[index]);

            // If not found, append arg name instead
            if (argValueMapPtr == argValMap->end())
            {
                // cout << "ADD ARG NAME:  " << template_ptr->argContentList[index] << endl;
                ret += template_ptr->argContentList[index];
            }
            else
            {
                // cout << "ADD ARG VAL: " << argValueMapPtr->second << endl;
                ret += argValueMapPtr->second;
            }
        }
    }

    argValMap->clear();
    return ret;
}