#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<cassert>

#include"../include/helpers.hpp"

using namespace std;

/** 
 * Data provider for testToLowerCase
 */
vector<tuple<string,string,string>> testToLowerCaseProvider(){
    string temp = "abc";
    string endsWithTerminator = temp+'\0';
    return {
        make_tuple("Ends With Terminator",endsWithTerminator,temp),
        make_tuple("All Small","allsmall","allsmall"),
        make_tuple("All CAPS","ALLCAPS","allcaps"),
        make_tuple("Spaced words","spaced words","spaced_words"),
        make_tuple("Caps spaced","CAPS and SPACED","caps_and_spaced"),
        make_tuple("Numbers","call 911","call_911")       
    };
}

/**
 * testToLowerCase
 */
void testToLowerCase()
{          
    cout << "Testing testToLowerCase---" << endl;

    vector<tuple<string,string,string>> tests = testToLowerCaseProvider();
    for(auto test : tests){
        
        string testname = get<0>(test);
        string input = get<1>(test);
        string expected = get<2>(test);

        string actual = toLowerCase(input); 
        
        if( actual == expected){
            cout << "  PASSED OK " << testname << endl;
        } else {
            cout << "  FAILED XX " << testname << endl;
            cout << "    INPUT : " << input << endl; 
            cout << "    EXPECTED : " << expected << endl; 
            cout << "    ACTUAL : " << actual << endl; 
            assert(0);
        }
        
    }
}

/** 
 * Data provider for testParseLinks
 */
vector<tuple<string,string,string,string>> testParseLinksProvider(){
    string path = "../site/";
    
    vector<tuple<string,string,string,string>> testParams;
    vector<tuple<string,string,string,string>> linkTests = {
        make_tuple(
            "Correct Link",
            "[urlText](url)",
            path,
            "<a href='url'>urlText</a>"),
        make_tuple(
            "Inline link with text",
            "text [urlText](url) text",
            path,
            "text <a href='url'>urlText</a> text"),
        make_tuple(
            "Multiple Inline link with text",
            "text [urlText](url) text [urlText](url) text",
            path,
            "text <a href='url'>urlText</a> text <a href='url'>urlText</a> text"),
        make_tuple(
            "Incorrect link syntax : missing [",
            "urlText](url)",
            path,
            "urlText](url)"),
        make_tuple(
            "Incorrect link syntax : missing ]",
            "[urlText(url)",
            path,
            "[urlText(url)"),
        make_tuple(
            "Incorrect link syntax : missing (",
            "[urlText]url)",
            path,
            "[urlText]url)"),
        make_tuple(
            "Incorrect link syntax : missing )",
            "[urlText](url",
            path,
            "[urlText](url"),
        make_tuple(
            "Incorrect link syntax with correct link : [text",
            "[text [urlText](url)",
            path,
            "[text <a href='url'>urlText</a>"),
        make_tuple(
            "Incorrect link syntax with correct link : text]",
            "text] [urlText](url)",
            path,
            "text] <a href='url'>urlText</a>"),
        make_tuple(
            "Incorrect link syntax : [text]",
            "[text]",
            path,
            "[text]"),
        make_tuple(
            "Nested links",
            "[urlTextOuter [urlText](url)](urlOutside)",
            path,
            "[urlTextOuter <a href='url'>urlText</a>](urlOutside)"),
        };
    vector<tuple<string,string,string,string>> imageLinks = {

        make_tuple(
            "Correct Image",
            "![altText](url)",
            path,
            "<img src='url' alt='altText'>"),

        make_tuple(
            "Optinal AltText Image",
            "![](url)",
            path,
            "<img src='url' alt=''>"),

        make_tuple(
            "Inline Image",
            "text ![altText](url) text",
            path,
            "text <img src='url' alt='altText'> text"),

        make_tuple(
            "Multiple Image",
            "![altText](url) ![altText](url)",
            path,
            "<img src='url' alt='altText'> <img src='url' alt='altText'>"),

        make_tuple(
            "Broken Image : Missing ]",
            "![altText (url)",
            path,
            "![altText (url)"),

        make_tuple(
            "Missing image link",
            "![altText]",
            path,
            "![altText]")
    };

    testParams.insert(testParams.begin(),imageLinks.begin(),imageLinks.end());
    testParams.insert(testParams.begin(),linkTests.begin(),linkTests.end());
    return testParams;
}

/**
 * testParseLinks
 */
void testParseLinks()
{          
    cout << "Testing testParseLinks ----" << endl;

    vector<tuple<string,string,string,string>> tests = testParseLinksProvider();
    for(auto test : tests){
        
        string testname = get<0>(test);
        string input1 = get<1>(test);
        string input2 = get<2>(test);
        string expected = get<3>(test);

        string actual = parseLinks(input1, input2); 
        
        if( actual == expected){
            cout << "  PASSED OK " << testname << endl;
        } else {
            cout << "  FAILED XX " << testname << endl;
            cout << "    INPUT TEXT : " << input1 << endl; 
            cout << "    INPUT PATH : " << input2 << endl; 
            cout << "    EXPECTED : " << expected << endl; 
            cout << "    ACTUAL : " << actual << endl; 
            assert(0);
        }
        
    }
}