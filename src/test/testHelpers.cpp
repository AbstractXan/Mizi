#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>

#include "../include/helpers.hpp"
#include "../include/template.hpp"

using namespace std;

string HELPER_DOMAIN = "helpers/";
/** 
 * Data provider for testTokenizer
 * @param void
 * @return [ Line, Delims, Expected Tokens ]
 */
vector<tuple<string, string, string, vector<string>>> testTokenizerProvider()
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
 * Tests tokenizer()
 */
void testTokenizer()
{
    cout << HELPER_DOMAIN << "tokenizer" << endl;

    vector<tuple<string, string, string, vector<string>>> tests = testTokenizerProvider();
    int passed = 0;

    for (auto test : tests)
    {

        string testname = get<0>(test);
        string input = get<1>(test);
        string delims = get<2>(test);
        vector<string> expected = get<3>(test);

        vector<string> actual = tokenizer(input, delims);

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

/** 
 * Data provider for testToLowerCase
 */
vector<tuple<string, string, string>> testToLowerCaseProvider()
{
    string temp = "abc";
    string endsWithTerminator = temp + '\0';
    return {
        make_tuple("Ends With Terminator", endsWithTerminator, temp),
        make_tuple("All Small", "allsmall", "allsmall"),
        make_tuple("All CAPS", "ALLCAPS", "allcaps"),
        make_tuple("Spaced words", "spaced words", "spaced_words"),
        make_tuple("Caps spaced", "CAPS and SPACED", "caps_and_spaced"),
        make_tuple("Numbers", "call 911", "call_911")};
}

/**
 * testToLowerCase
 */
void testToLowerCase()
{
    cout << HELPER_DOMAIN << "toLowerCase" << endl;

    vector<tuple<string, string, string>> tests = testToLowerCaseProvider();
    int passed = 0;

    for (auto test : tests)
    {

        string testname = get<0>(test);
        string input = get<1>(test);
        string expected = get<2>(test);

        string actual = toLowerCase(input);

        if (actual == expected)
        {
            //cout << "  PASSED OK " << testname << endl;
            passed++;
        }
        else
        {
            cout << "  FAILED XX " << testname << endl;
            cout << "    INPUT : " << input << endl;
            cout << "    EXPECTED : " << expected << endl;
            cout << "    ACTUAL : " << actual << endl;
            assert(0);
        }
    }
    cout << "    " << passed << "/" << tests.size() << " TESTS PASSED " << endl;
}

/** 
 * Data provider for testParseLinks
 * Tests images, links and template
 * @see testTemplateManager for more template rendering related tests
 */
vector<tuple<string, string, string, TemplateManager *, string>> testParseLinksProvider()
{
    string path = "site/";

    vector<tuple<string, string, string, TemplateManager *, string>> testParams;

    vector<tuple<string, string, string, TemplateManager *, string>> imageTests = {

        make_tuple(
            "Correct Image",
            "![altText](url)",
            path,
            nullptr,
            "<img src='url' alt='altText'>"),

        make_tuple(
            "Optinal AltText Image",
            "![](url)",
            path,
            nullptr,
            "<img src='url' alt=''>"),

        make_tuple(
            "Inline Image",
            "text ![altText](url) text",
            path,
            nullptr,
            "text <img src='url' alt='altText'> text"),

        make_tuple(
            "Multiple Image",
            "![altText](url) ![altText](url)",
            path,
            nullptr,
            "<img src='url' alt='altText'> <img src='url' alt='altText'>"),

        make_tuple(
            "Broken Image : Missing ]",
            "![altText (url)",
            path,
            nullptr,
            "![altText (url)"),

        make_tuple(
            "Missing image link",
            "![altText]",
            path,
            nullptr,
            "![altText]"),
    };

    vector<tuple<string, string, string, TemplateManager *, string>> testLinks = {

        make_tuple(
            "Correct Link",
            "[urlText](url)",
            path,
            nullptr,
            "<a href='url'>urlText</a>"),

        make_tuple(
            "Inline link with text",
            "text [urlText](url) text",
            path,
            nullptr,
            "text <a href='url'>urlText</a> text"),

        make_tuple(
            "Multiple Inline link with text",
            "text [urlText](url) text [urlText](url) text",
            path,
            nullptr,
            "text <a href='url'>urlText</a> text <a href='url'>urlText</a> text"),

        make_tuple(
            "Incorrect link syntax : missing [",
            "urlText](url)",
            path,
            nullptr,
            "urlText](url)"),

        make_tuple(
            "Incorrect link syntax : missing ]",
            "[urlText(url)",
            path,
            nullptr,
            "[urlText(url)"),

        make_tuple(
            "Incorrect link syntax : missing (",
            "[urlText]url)",
            path,
            nullptr,
            "[urlText]url)"),

        make_tuple(
            "Incorrect link syntax : missing )",
            "[urlText](url",
            path,
            nullptr,
            "[urlText](url"),

        make_tuple(
            "Incorrect link syntax with correct link : [text",
            "[text [urlText](url)",
            path,
            nullptr,
            "[text <a href='url'>urlText</a>"),

        make_tuple(
            "Incorrect link syntax with correct link : text]",
            "text] [urlText](url)",
            path,
            nullptr,
            "text] <a href='url'>urlText</a>"),

        make_tuple(
            "Incorrect link syntax : [text]",
            "[text]",
            path,
            nullptr,
            "[text]"),

        make_tuple(
            "Nested links",
            "[urlTextOuter [urlText](url)](urlOutside)",
            path,
            nullptr,
            "[urlTextOuter <a href='url'>urlText</a>](urlOutside)"),
    };

    // TEMPLATES
    TemplateManager tmpMgr("test/testFiles/testTemplates.conf");
    vector<tuple<string, string, string, TemplateManager *, string>> templateTests = {
        make_tuple(
            "Correct template -- no args",
            "{{Card}}",
            path,
            &tmpMgr,
            "title : desc"),
        make_tuple(
            "Correct template -- one arg",
            "{{Card title=Title}}",
            path,
            &tmpMgr,
            "Title : desc"),
        make_tuple(
            "Correct template -- two args",
            "{{Card title=Title desc=Desc}}",
            path,
            &tmpMgr,
            "Title : Desc"),
        make_tuple(
            "Wrong template",
            "text {{Card text",
            path,
            &tmpMgr,
            "text {{Card text"),
        make_tuple(
            "Wrong template - missing {",
            "text {Card text",
            path,
            &tmpMgr,
            "text {Card text"),
        make_tuple(
            "Template for header",
            "# {{Card title=Title desc=Desc}}",
            path,
            &tmpMgr,
            "# Title : Desc"),
        make_tuple(
            "Template for page",
            "## {{Card title=Title desc=Desc}}",
            path,
            &tmpMgr,
            "## Title : Desc"),
        make_tuple(
            "Template for header",
            "### {{Card title=Title desc=Desc}}",
            path,
            &tmpMgr,
            "### Title : Desc"),

    };

    testParams.insert(testParams.begin(), templateTests.begin(), templateTests.end());
    testParams.insert(testParams.begin(), imageTests.begin(), imageTests.end());
    testParams.insert(testParams.begin(), testLinks.begin(), testLinks.end());
    return testParams;
}

/**
 * testParseLinks
 */
void testParseLinks()
{
    cout << HELPER_DOMAIN << "parseLinks" << endl;

    vector<tuple<string, string, string, TemplateManager *, string>> tests = testParseLinksProvider();

    int passed = 0;
    for (auto test : tests)
    {

        string testname = get<0>(test);
        string input1 = get<1>(test);
        string input2 = get<2>(test);
        TemplateManager *tmag = get<3>(test);
        string expected = get<4>(test);

        string actual = parseLinks(input1, input2, tmag);

        if (actual == expected)
        {
            //cout << "  PASSED OK " << testname << endl;

            passed++;
        }
        else
        {
            cout << "  FAILED XX " << testname << endl;
            cout << "    INPUT TEXT : " << input1 << endl;
            cout << "    INPUT PATH : " << input2 << endl;
            cout << "    EXPECTED : " << expected << endl;
            cout << "    ACTUAL : " << actual << endl;
            assert(0);
        }
    }
    cout << "    " << passed << "/" << tests.size() << " TESTS PASSED " << endl;
}

void testHelpers()
{
    testTokenizer();
    testToLowerCase();
    testParseLinks();
}