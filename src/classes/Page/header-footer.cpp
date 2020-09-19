#include<string>
#include "../Config/config.hpp"

using namespace std;
string static getHeader(Config *conf){
    return "<header>" + conf->header + "</header>"; 
}

string static getFooter(Config *conf){
   return "<footer><p>" + conf->footer + "</p></footer>"; 
}
