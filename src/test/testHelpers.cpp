#include<iostream>
#include<string>
#include<vector>
#include<tuple>

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
    cout << "Testing testToLowerCase..." << endl;

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

