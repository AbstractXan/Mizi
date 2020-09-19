#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../Page/head.hpp"
#include "../Page/header-footer.cpp"
#include "../../helpers/helpers.hpp"
#include "../Category/category.hpp"
#include "home.hpp"

void buildHome(Config *conf, Category *categories[], int categories_length, string path) {
  ofstream htmlHome;
  htmlHome.open(path + "/home.html");
  htmlHome << html_head(conf, "Home");
  htmlHome << getHeader(conf);
  htmlHome << "<main class='home'>";

  for (int i = 1; i <= categories_length; i++) {
    Category *category = categories[i];
    htmlHome << "<h2>" << category->name << "</h2>";
    htmlHome << "<ul>";
    for (int j = 0; j < category->pageCount; j++) {
      Page *page = category->pages[j];
      string page_name = page->title;
      string page_index = toLowerCase(page_name);
      htmlHome << "<li><a href='" << page_index << ".html'>" << page_name
               << "</a></li>";
    }

    htmlHome << "</ul>";
  }
  htmlHome << "<hr/>";
  htmlHome << "</main>";
  htmlHome << getFooter(conf);
  htmlHome << "</body></html>";
  htmlHome.close();
}

