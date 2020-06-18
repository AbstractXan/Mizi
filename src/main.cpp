#include<fstream>
#include"mizi.cpp"
using namespace std;


int main(int argc,char *argv[]){
    
    for (int i=0 ; i < argc; i++){
        string arg(argv[i]);
        if ( arg == "-a"){
            createSite("../archive/archive.md","../site/");
        }
    }
    createSite("website.md","../site/");
    return 0;
}