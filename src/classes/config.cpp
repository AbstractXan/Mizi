#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/config.hpp"
#include "../include/helpers.hpp"

using namespace std;

Config * configParser()
{
  Config *conf = new Config;
  ifstream configFile("config.txt");
  if (configFile.is_open())
  {
    string line;
    while (getline(configFile, line))
    {
      istringstream is_line(line);
      string key;
      if (getline(is_line, key, '='))
      {
        string value;
        if (getline(is_line, value))
        {
          if (key == "shortcut_icon")
          {
            conf->shortcut_icon = value;
          }
          else if (key == "icon")
          {
            conf->icon = value;
          }
          else if (key == "name")
          {
            conf->name = value;
          }
          else if (key == "description")
          {
            conf->description = value;
          }
          else if (key == "creator")
          {
            conf->twitter_creator = value;
          }
          else if (key == "header")
          {
            conf->header = value;
          }
          else if (key == "footer")
          {
            conf->footer = value;
          }
          else
          {
            cout << "Config file syntax error." << endl;
          }
        }
      }
    }
  }
  configFile.close();
  return conf;
}
