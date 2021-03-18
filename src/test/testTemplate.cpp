#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>

#include "../include/template.hpp"

using namespace std;

string TEMPLATE_DOMAIN = "template/";

/** 
 * Data provider for testSplit
 * Returns <line,delims,expected_tokens> 
 */
vector<tuple<string, string, string, vector<string>>> testSplitProvider()
{
    return {
        // Tests for splits used in templates
        make_tuple(
            "FUNC(ARG1)",
            "func(arg1)",
            "(,)",
            vector<string>({"func", "arg1"})),
        make_tuple(
            "FUNC(ARG1,ARG2)",
            "func(arg1,arg2)",
            "(,)",
            vector<string>({"func", "arg1", "arg2"})),
        make_tuple(
            "FUNC(ARG1,ARG2,ARG3)",
            "func(arg1,arg2,arg3)",
            "(,)",
            vector<string>({"func", "arg1", "arg2", "arg3"})),

    };
}

/**
 * Tests split()
 */
void testSplit()
{
    cout << TEMPLATE_DOMAIN << "split" << endl;

    vector<tuple<string, string, string, vector<string>>> tests = testSplitProvider();
    int passed = 0;

    for (auto test : tests)
    {

        string testname = get<0>(test);
        string input = get<1>(test);
        string delims = get<2>(test);
        vector<string> expected = get<3>(test);

        vector<string> actual = split(input, delims);

        if (actual == expected)
        {
            //cout << "  PASSED OK " << testname << endl;
            passed++;
        }
        else
        {
            cout << "  FAILED XX " << testname << endl;
            cout << "    INPUT : " << input << endl;
            cout << "    EXPECTED : " << expected.size() << " tokens" << endl;
            cout << "    ACTUAL : " << actual.size() << " tokens" << endl;
            assert(0);
        }
    }
    cout << "    " << passed << "/" << tests.size() << " TESTS PASSED " << endl;
}

void testTemplate()
{
    testSplit();
}