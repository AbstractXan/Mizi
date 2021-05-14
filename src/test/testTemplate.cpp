#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>

#include "../include/template.hpp"
#include "./support/testHelperFunctions.cpp"

using namespace std;

string TEMPLATE_DOMAIN = "template/";

/** 
 * Data provider for testToLowerCase
 */
vector<pair<string, vector<string>>> testGenerateTemplateArgValueMapProvider()
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
    cout << TEMPLATE_DOMAIN << "generateTemplateArgValueMap" << endl;

    vector<pair<string, vector<string>>> tests = testGenerateTemplateArgValueMapProvider();

    int passed = 0;

    TemplateManager tmpMgr("test/testFiles/testTemplates.txt");
    for (auto test : tests)
    {
        string testname = test.first;
        vector<string> input = test.second;

        std::unordered_map<std::string, std::string> *argMap = tmpMgr.generateTemplateArgValueMap(input);

        bool hasErrors = false;
        for (size_t index = 1; index < input.size(); index++)
        {
            if (index % 2 == 1)
            {
                auto map_itr = argMap->find(input[index]);

                // has errors if arg not found in map / value not stored correctly
                if (map_itr == argMap->end() || map_itr->second != input[index + 1])
                {
                    hasErrors = true;
                }
            }
        }

        if (!hasErrors)
        {
            //cout << "  PASSED OK " << testname << endl;
            passed++;
        }
        else
        {
            cout << "  FAILED XX " << testname << endl;
            cout << "    INPUT : " << printVector(input) << endl;
            //cout << "    EXPECTED : " << expected << endl;
            //cout << "    ACTUAL : " << actual << endl;
            assert(0);
        }
    }

    cout << "    " << passed << "/" << tests.size() << " TESTS PASSED " << endl;
}

/** 
 * Data provider for testParseAndSaveTemplateContent
 * @return [TestName, ContentLine, ExpectedText, ExpectedArgs]
 */
vector<tuple<string, string, vector<string>, vector<string>>> testParseAndSaveTemplateContentProvider()
{
    vector<tuple<string, string, vector<string>, vector<string>>> testParams;
    vector<tuple<string, string, vector<string>, vector<string>>> happyPathTestParams = {
        make_tuple(
            "Content with No Arg",
            "Hello World",
            vector<string>({"Hello World"}),
            vector<string>({})),

        make_tuple(
            "Content with One Arg",
            "Hello $$world$$",
            vector<string>({"Hello ", ""}),
            vector<string>({"world"})),

        make_tuple(
            "Content with Two Args",
            "Hello $$world$$ $$arg2$$",
            vector<string>({"Hello ", " ", ""}),
            vector<string>({"world", "arg2"})),

        make_tuple(
            "Content with no text",
            "",
            vector<string>({""}),
            vector<string>({})),

        make_tuple(
            "Content with no text and one arg",
            "$$arg$$",
            vector<string>({"", ""}),
            vector<string>({"arg"})),

        make_tuple(
            "Content with no text and two arg",
            "$$arg$$$$arg2$$",
            vector<string>({"", "", ""}),
            vector<string>({"arg", "arg2"})),
    };

    vector<tuple<string, string, vector<string>, vector<string>>> errorPathTestParams = {
        make_tuple(
            "Content with missing starting '$'",
            "$arg$$",
            vector<string>({"$arg$$"}),
            vector<string>({})),
        make_tuple(
            "Content with missing end '$'",
            "$$arg$",
            vector<string>({"$$arg$"}),
            vector<string>({})),
        make_tuple(
            "Content with correct and wrong arg syntax",
            "$$arg1$$ $$arg$",
            vector<string>({""," $$arg$"}),
            vector<string>({"arg1"})),
        make_tuple(
            "Content with space in arg name",
            "$$arg $$",
            vector<string>({"$$arg $$"}),
            vector<string>({})),
    };

    testParams.insert(testParams.begin(), errorPathTestParams.begin(), errorPathTestParams.end());
    testParams.insert(testParams.begin(), happyPathTestParams.begin(), happyPathTestParams.end());
    return testParams;
}

/**
 * testParseAndSaveTemplateContent
 */
void testParseAndSaveTemplateContent()
{
    cout << TEMPLATE_DOMAIN << "parseAndSaveTemplateContent" << endl;

    vector<tuple<string, string, vector<string>, vector<string>>> tests = testParseAndSaveTemplateContentProvider();
    int passed = 0;

    for (auto test : tests)
    {
        string testname = get<0>(test);
        string input = get<1>(test);
        vector<string> expectedText = get<2>(test);
        vector<string> expectedArgs = get<3>(test);

        Template *tempPtr = new Template;
        parseAndSaveTemplateContent(tempPtr, input);

        bool argsMatch = tempPtr->args == expectedArgs;
        bool textMatch = tempPtr->text == expectedText;
        if (argsMatch && textMatch)
        {
            //cout << "  PASSED OK " << testname << endl;
            passed++;
        }
        else
        {
            cout << "  FAILED XX " << testname << endl;
            cout << "    INPUT : " << input << endl;
            cout << "    EXPECTED ARGS : " << printVector(expectedArgs) << endl;
            cout << "    ACTUAL ARGS: " << printVector(tempPtr->args) << endl;
            cout << "    EXPECTED TEXT : " << printVector(expectedText) << endl;
            cout << "    ACTUAL TEXT: " << printVector(tempPtr->text) << endl
                 << endl;
            //assert(0);
        }
    }
    cout << "    " << passed << "/" << tests.size() << " TESTS PASSED " << endl;
}

void testTemplate()
{
    testGenerateTemplateArgValueMap();
    testParseAndSaveTemplateContent();
}