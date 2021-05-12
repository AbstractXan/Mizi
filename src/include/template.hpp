#pragma once

#include <string>
#include <vector>
#include <map>

struct Template
{
  std::string name;
  std::vector<std::string> args;

  std::vector<std::string> text;
  std::vector<std::string> argOrder;
};

typedef std::map<std::string, Template *> TemplateMap;

class TemplateManager
{
  private:
  void templateCreatorParser(std::string templateFile);
  TemplateMap *tmap;

  public:
  TemplateManager(std::string templateFile);
  // Read string from md like: {{template}}
  std::string templateReaderParser(std::string);
  std::string templateRenderer();
};
