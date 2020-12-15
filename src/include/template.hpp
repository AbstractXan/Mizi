#pragma once

#include<string>
#include<vector>
#include <map>


struct Template
{
  std::string name;
  std::vector<std::string> args;
};
typedef std::map<std::string,Template*> TemplateMap;

TemplateMap* templateParser();