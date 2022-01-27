#include <fstream>
#include <string>
#include "../include/config.hpp"
#include "../include/helpers.hpp"
#include "../include/header-footer.hpp"
#include "../include/page.hpp"
#include "../include/head.hpp"

using namespace std;

Page *createPage(string title)
{
  Page *newpage = new Page;
  newpage->title = title;
  newpage->partsCount = 0;
  return newpage;
}

void addPart(Page *page, string name)
{
  page->partName[page->partsCount] = name;
  page->partsCount++;
}

void buildPage(Config *conf, Page *page, string path)
{
  ofstream htmlPage;
  string filename = toLowerCase(page->title);
  string filepath = path + filename + ".html";
  htmlPage.open(filepath.c_str());
  htmlPage << html_head(conf, page->title);
  htmlPage << getHeader(conf);
  htmlPage << "<main class='page'>" << "\n";
  htmlPage << "<h1>" << page->title << "</h1>\n";

  if (page->partsCount >= 3)
  {
    htmlPage << "<ul class='jump'>\n";
    for (int i = 0; i < page->partsCount; i++)
    {
      string part_name = page->partName[i];
      string part_index = toLowerCase(part_name);
      htmlPage << "<li><a href='#" << part_index << "'>" << part_name
               << "</a></li>\n";
    }

    // Fix for <ul> overflow from createCategories()
    htmlPage << "</ul>\n";
  }

  for (int i = 0; i < page->partsCount; i++)
  {
    string part_name = page->partName[i];
    string part_desc = page->partDesc[i];
    string part_index = toLowerCase(part_name);
    htmlPage << "</ul><h2 id='" << part_index << "'>" << part_name
             << "</h2>\n"; // Extra </ul> to keep a check on overflowing <ul>
    htmlPage << part_desc << "\n";
  }

  htmlPage << "<hr/>";
  htmlPage << "</main>";
  htmlPage << getFooter(conf) << "\n";
  htmlPage << "</body></html>";
  htmlPage.close();
}
