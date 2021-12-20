#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/config.hpp"
#include "../include/helpers.hpp"

using namespace std;
std::string defaultConfig("shortcut_icon=../media/interface/favicon.ico\nicon=../media/interface/favicon.ico\nname=Mizi\ndescription=Site generated using Mizi\ncreator=abstractxan\nheader=<a id='logo' href='home.html'><img src='../media/interface/logo.png' alt='logo' ></a>\nfooter=<p>Website generated using <u><a href='https://github.com/abstractxan/Mizi'>abstractxan/Mizi</a><u></p>\ntemplatefile=template.txt");

Config *configParser()
{
  Config *conf = new Config;
  ifstream configFile("config.txt");
  if (!configFile.is_open())
  {
    // Create default config.txt when not present
    fstream configFileWrite("config.txt", std::ios_base::app);
    configFileWrite.write(defaultConfig.data(), defaultConfig.size());
    configFileWrite.close();

    configFile.open("config.txt");
  }
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
        else if (key == "templatefile")
        {
          conf->templatefile = value;
        }
        else
        {
          cout << "Config file syntax error." << endl;
        }
      }
    }
  }

  configFile.close();
  return conf;
}
