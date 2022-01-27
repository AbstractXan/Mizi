#include "../include/config.hpp"
#include <string>
#include "../include/head.hpp"

using namespace std;

string html_head(Config *conf, string text)
{
  return "<!DOCTYPE html><html lang='en'><head><link rel='shortcut icon' "
         "href='" +
         conf->shortcut_icon + "' type='image/x-icon'><link rel='icon' href='" +
         conf->icon +
         "' type='image/x-icon'><meta charset='utf-8'><meta name='description' "
         "content='" +
         conf->description +
         "'><meta name='viewport' content='width=device-width, "
         "initial-scale=1.0'><meta name='twitter:card' content='summary'><meta "
         "name='twitter:site' content='" +
         conf->name + "'><meta name='twitter:title' content='" + conf->name +
         "'><meta name='twitter:description' content='" + conf->description +
         "'><meta name='twitter:creator' content='@" + conf->twitter_creator +
         "'><meta name='twitter:image' content='" + conf->icon +
         "'><meta property='og:title' content='" + conf->name +
         "'><meta property='og:site_name' content='" + conf->name +
         "'><title> " + conf->name + " - " + text +
         "</title><link rel='stylesheet' type='text/css' "
         "href='" +
         conf->css + "'>" + conf->head + "</head><body class='" +
         text + "'>\n";
}
