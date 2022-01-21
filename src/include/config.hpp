#pragma once

#include <string>

struct Config
{
  std::string shortcut_icon;
  std::string icon;
  std::string name;
  std::string description;
  std::string twitter_creator;
  std::string header;
  std::string footer;
  std::string templatefile;
  std::string css;
  std::string site;
  std::string head; // used for adding scripts to <head>
};

Config *configParser();
