#include <fstream>
#include "include/site.hpp"
#include "test/test.cpp"

using namespace std;

int main(int argc, char *argv[])
{

    for (int i = 0; i < argc; i++)
    {
        string arg(argv[i]);
        if (arg == "-t")
        {
            runTests();
            return 0;
        }
    }

    createSite("website.md", "site/");
    return 0;
}
