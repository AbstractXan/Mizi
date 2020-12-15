#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/template.hpp"
#include "../include/helpers.hpp"

using namespace std;

// Tokenizes based on delims
void split(const std::string& str, vector<string>& cont,const std::string& delims = " ")
{
    std::size_t current, previous = 0;
    current = str.find_first_of(delims);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find_first_of(delims, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
}

TemplateMap * templateParser()
{
  TemplateMap *tmap = new TemplateMap;

  Template *currTemplate;
  bool isParsingTemplateText = false;

  ifstream templateFile("template.txt");
  if (templateFile.is_open())
  {
    string line;
    while (getline(templateFile, line))
    {
        size_t i=0;

        if(line.size()<1){
            // blanks
            continue;
        }

        // Parse line
        while(i<line.size())
        {
            // if @@ => Create || create newTemplateFunction
            if(line[i]=='@' && line[i+1]=='@')
            {
                
                if(isParsingTemplateText){
                    tmap->insert(pair<std::string,Template*>(currTemplate->name,currTemplate));
                    isParsingTemplateText=false;
                    break;
                }
                i+=2;
                // create template
                currTemplate = new Template;
                vector<string> tokens;
                split(line.substr(i, line.size() - i + 1),tokens,"@(,)");

                // Debug print args
                for(auto s: tokens){
                    cout << s << endl;
                }

                // Assign temporarily
                currTemplate->name = tokens[0];
                tokens.erase(tokens.begin()); // Remove name from args;
                currTemplate->args = tokens;

                isParsingTemplateText = true;
                break;
            }
            i++;
        }
    }
    templateFile.close();
  }
  return tmap;
}

string templateRederer(){
    
}