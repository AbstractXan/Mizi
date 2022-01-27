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
  std::string templatefile; // deafult: "template.conf"
  std::string css; // default: "../style.css" relative to html files
  std::string site; // default: "site/" relative to mizi
  std::string head; // used for adding scripts to <head>
};

Config *configParser();
