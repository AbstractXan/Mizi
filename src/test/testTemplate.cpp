#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>

#include "../include/template.hpp"

using namespace std;

string TEMPLATE_DOMAIN = "template/";

/** 
 * Data provider for testToLowerCase
 */
vector<pair<string, vector<string>>> testToGenerateTemplateArgValueMap()
{
   vector<string> temp1 = {"template name", "arg1", "val1", "arg2", "val2", "arg3", "val3"};
   vector<string> temp2 = {"template name"};
   return {
       make_pair("test 1", temp1),
       make_pair("no arg no val", temp2),
   };
}
/**
 * testToLowerCase
 */
void testGenerateTemplateArgValueMap()
{
   cout << HELPER_DOMAIN << "generateTemplateArgValueMap" << endl;

   vector<pair<string, vector<string>>> tests = testToGenerateTemplateArgValueMap();

   int passed = 0;

   TemplateManager tmpMgr("test/testFiles/testTemplates.txt");
   for (auto test : tests)
   {
      string testname = test.first;
      vector<string> input = test.second;

      std::unordered_map<std::string, std::string> *argMap = tmpMgr.generateTemplateArgValueMap(input);
      int allok = 1;
      for (size_t i = 1; i < input.size(); i++)
      {
         if (i % 2 == 1)
         {
            auto map_itr = argMap->find(input[i]);
            if (map_itr == argMap->end())
            {
               allok = 0;
            }
            else if (map_itr->second != input[i + 1])
            {
               allok = 0;
            }
         }
      }

      if (allok == 1)
      {
         cout << "  PASSED OK " << testname << endl;
         passed++;
      }
      else
      {
         cout << "  FAILED XX " << testname << endl;
         //cout << "    INPUT : " << input << endl;
         //cout << "    EXPECTED : " << expected << endl;
         //cout << "    ACTUAL : " << actual << endl;
         assert(0);
      }
   }
   cout << "    " << passed << "/" << tests.size() << " TESTS PASSED " << endl;
}

void testTemplate()
{
   testGenerateTemplateArgValueMap();
}