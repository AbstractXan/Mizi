#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(){
    //Open file
    string line;

    string categories[] = {};
    ifstream mdFile ("website.md");
    if (mdFile.is_open())
    {
        while ( getline (mdFile,line) )
        {
            int hashcount=0;
            int i=0;
            string currentCategory;
            
            while(line[i]=='#'){
                hashcount++;
                i++;
            }

            // Category
            if(hashcount==1){
                currentCategory = line.substr(i+1,line.size()-i);
                cout << currentCategory;
            }
            if(hashcount==2){   
                if (currentCategory.empty()){
                    cout << "Error! No Category assigned!\n";
                    return 0;
                }
            }
        }
        mdFile.close();
    }

    else cout << "Unable to open file\n"; 

    return 0;
}