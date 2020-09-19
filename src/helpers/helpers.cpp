#include <string>
#include <iostream>

using namespace std;
char static getLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - ('Z' - 'z');
    return c;
}
string static toLowerCase(string text)
{
    string newtext = "";
    for (unsigned int i = 0; i < text.size(); i++)
    {
        if (text[i] == '\0')
            break;
        else if (text[i] == ' ')
            newtext += '_';
        else if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z')) //alphabets
            newtext += getLower(text[i]);
        else if (text[i] >= '0' && text[i] <= '9')
            newtext += getLower(text[i]);
    }
    return newtext;
}
// Prints errorline
void static printError(int linenumber, string text) {
  cout << "Error at line " << linenumber << ". " << text << endl;
}