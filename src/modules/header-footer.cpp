#include<string>
#include "../include/helpers.hpp"
#include "../include/config.hpp"

using namespace std;
string getHeader(Config *conf){
    return "<header>" + conf->header + "</header>"; 
}

string getFooter(Config *conf){
   return "<footer><p>" + conf->footer + "</p></footer>"; 
}
