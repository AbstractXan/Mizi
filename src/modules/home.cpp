#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/head.hpp"
#include "../include/header-footer.hpp"
#include "../include/helpers.hpp"
#include "../include/category.hpp"
#include "../include/home.hpp"

using namespace std;


std::string buildHome(Config *conf, Category *categories[], int categories_length, string path) {
  ofstream htmlHome;
  htmlHome.open(path + "/home.html");
  string home = "";
  home += html_head(conf, "Home");
  home += getHeader(conf);
  home += "<main class='home'>";

  string nav = ""; //create nav for every page

  for (int i = 1; i <= categories_length; i++) {
    Category *category = categories[i];

    home = home + "<h2>" + category->name + "</h2>";
    home += "<ul>";

    nav = nav + "<h2>" + category->name + "</h2>";
    nav += "<ul>";

    for (int j = 0; j < category->pageCount; j++) {
      Page *page = category->pages[j];
      string page_name = page->title;
      string page_desc = page->description;
      string page_index = toLowerCase(page_name);

      home = home + 
            "<li><a href='" + page_index + ".html'>" + page_name + "</a> <div class='pagedesc'> " + page_desc + "</div></li>";
      
      //nav takes no description
      nav = nav + "<li><a href='" + page_index + ".html'>" + page_name + "</a>";
    }
    home += "</ul>";
    nav += "</ul>";
  }
  home += "<hr/>";
  home += "</main>";
  home += getFooter(conf);
  home += "</body></html>";
  htmlHome << home;
  htmlHome.close();
  return nav;
}

