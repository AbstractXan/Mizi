#include <string>
#include <iostream>

#include "../include/helpers.hpp"
#include "../include/template.hpp"

using namespace std;
char getLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - ('Z' - 'z');
    return c;
}

string toLowerCase(string text)
{
    string newtext = "";
    for (unsigned int i = 0; i < text.size(); i++)
    {
        if (text[i] == '\0')
            break;
        else if (text[i] == ' ')
            newtext += '_';
        else if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')) //alphabets
            newtext += getLower(text[i]);
        else if (text[i] >= '0' && text[i] <= '9')
            newtext += text[i];
    }
    return newtext;
}
// Prints errorline
void printError(int linenumber, string text)
{
    cout << "Error at line " << linenumber << ". " << text << endl;
}

/** 
 * Tokenizes string based on delims
 * @param stringPtr
 * @param delims Default value = " "
 */
vector<string> tokenizer(const std::string stringPtr, const std::string &delims = " ")
{

    vector<string> tokens;
    std::size_t nextIndex, currIndex = 0;
    // Find next instance of delim
    nextIndex = stringPtr.find_first_of(delims);
    // While delims exist
    while (nextIndex != std::string::npos)
    {
        // Add token
        tokens.push_back(stringPtr.substr(currIndex, nextIndex - currIndex));
        currIndex = nextIndex + 1;
        nextIndex = stringPtr.find_first_of(delims, currIndex);
    }
    // Push last string chunk
    if (currIndex < stringPtr.size())
    {
        tokens.push_back(stringPtr.substr(currIndex, stringPtr.size() - currIndex));
    }

    return tokens;
}

//  [urlText](url) ->  <a href='url'>urlText</a>
// ![altText](image) -> <img src='' alt=''>
// {{templateName param1=value1 param2=value2}}
string parseLinks(string text, string path, TemplateManager *templateMgr)
{
    path = "";
    string label = text;
    size_t index = 0;
    string newText = "";
    string urlText = "";
    string url = "";
    bool isImage = false;

    for (; index < text.size();)
    {

        // Check if template
        if (text[index] == '{' && index + 1 < text.size() && text[index + 1] == '{')
        {
            index += 2;

            string templateString = "";
            bool templateParseSuccessful = false;
            while (index < text.size())
            {
                if (text[index] == '}' && text[index + 1] == '}')
                {
                    templateParseSuccessful = true;
                    break;
                }
                templateString += text[index];
                index += 1;
            }

            if (templateParseSuccessful)
            {
                newText += templateMgr->renderTemplateFromText(templateString);
                index += 2;
            }
            else
            {
                newText += "{{" + templateString;
            }
        }

        // Enter into linking
        // ![ -> image flag true
        else if (text[index] == '!' && text[index + 1] == '[')
        {
            isImage = true;
            index++;
            continue;
        }
        else if (text[index] == '[')
        {

            // Crude implementation for images
            if (index >= 1 && text[index - 1] == '!')
            {
                isImage = true;
            }
            else
            {
                isImage = false;
            }

            index++;
            // Loop through urltext
            while (index < text.size() && text[index] != ']')
            {

                // Broken [text [text](link) case
                if (text[index] == '[')
                {
                    newText += '[' + urlText;
                    urlText = "";
                    index++;
                }

                urlText += text[index];
                index++;
            }

            // EndofUrlText
            // [urltext]
            if (text[index] == ']' && index < text.size())
            {
                index++;
                if (text[index] == '(' && index < text.size())
                {
                    index++;
                    // Continue
                    while (index < text.size() && text[index] != ')')
                    {

                        // Error [link](abc.com [link](abc.com)
                        if (text[index] == '[')
                        {
                            if (isImage)
                            {
                                newText += '!';
                            }

                            newText += '[' + urlText + "](" + url;
                            urlText = "";
                            break;
                        }
                        url += text[index];
                        index++;
                    }

                    // Complete parsing
                    if (text[index] == ')' && index < text.size())
                    {

                        if (isImage)
                        {
                            index++;
                            newText += "<img src='" + url + "' alt='" + urlText + "'>";
                        }
                        else
                        {
                            index++;
                            newText += "<a href='" + url + "'>" + urlText + "</a>";
                        }
                        url = "";
                        urlText = "";
                        isImage = false;
                        continue;
                    }

                    if (index == text.size())
                    {
                        if (isImage)
                        {
                            newText += '!';
                        }

                        newText += '[' + urlText + "](" + url;
                        continue;
                    }
                }
                else
                {
                    if (isImage)
                    {
                        newText += '!';
                    }
                    newText += '[' + urlText + ']';
                    urlText = "";
                    continue;
                }
            }
            else
            {
                if (isImage)
                {
                    newText += '!';
                }
                newText += '[' + urlText;
                urlText = "";
                continue;
            }
        }
        else
        {
            newText += text[index];
            index++;
        }
    }
    return newText;
}

/**
 * @brief Check CSS and Template file exist
 * @param *Config Pointer to config
 * @return void
 */
void checkProjectFileStructure(Config *conf)
{
    if (conf->css != "")
        createFileIfDNE(conf->css, "");

    if (conf->templatefile != "")
        createFileIfDNE(conf->templatefile, "");
}

/**
 * @brief Create a File If DNE 
 * @param path Path to the file
 * @param defaultData (optional) Default data used to create new file
 */
void createFileIfDNE(std::string path, std::string defaultData = "")
{
    std::ifstream file(path.data());

    if (!file.is_open())
    {
        cout << endl << "File '" + path + "' not found. Generating...";
        std::fstream fileWrite(path.data(), std::ios_base::app);
        fileWrite.write(defaultData.data(), defaultData.size());
        fileWrite.close();
        cout << "DONE" << endl;
    }
}