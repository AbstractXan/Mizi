#include<fstream>
#include"reader.h"

using namespace std;


int main(){ 
    string line;
    int lineNo=0;
    int categoryCount=0;

    Category * currentCategory; 
    Page * currentPage;   
    string currentPartName = "";
    string currentPartDesc = "";
    
    ifstream mdFile ("website.md");
    
    if (mdFile.is_open())
    {
        while ( getline (mdFile,line) )
        {
            lineNo++;
            int hashcount=0;
            int i=0;

            // Headings
            if (line[0]=='#'){
                while(line[i]=='#'){
                    hashcount++;
                    i++;
                }

                // Category
                if(hashcount==1){
                    currentCategory = createCategory(line.substr(i+1,line.size()-i),categoryCount++);
                }

                // Page
                else if(hashcount==2){   
                    if (currentCategory->name.empty()){
                        printError(lineNo,"No Category assigned!");
                        return 0;
                    }
                    currentPage = createPage(line.substr(i+1,line.size()-i));
                    addPage(currentCategory,currentPage);
                }

                // Part
                else if(hashcount==3){
                    if (currentCategory->name.empty()){
                        printError(lineNo,"No Category assigned!");
                        return 0;
                    }
                    if (currentPage->title.empty()){
                        printError(lineNo,"No Page assigned!");
                        return 0;
                    }
                    //Current Part Name
                    currentPartName = line.substr(i+1,line.size()-i);
                    addPart(currentPage,currentPartName);
                    currentPartDesc = "";
                }
            } 
            else //No headings
            {
                // Error
                if(currentPartName==""||currentPage->title.empty()){
                    printError(lineNo,"No Part assigned!");
                    return 0;
                }

                currentPartDesc+=line;
                currentPartDesc+="\n";
                if (currentPage->title != "")
                    currentPage->partDesc[(currentPage->partsCount)-1]=currentPartDesc;
            }
        }
        mdFile.close();
    }
    else cout << "Unable to open file"<<endl; 

    //Debug Refer 'reader.h'
    //printContent(Categories,categoryCount);

    cout << "Categories found: " << categoryCount << endl;
    createSite(Categories,categoryCount);
    return 0;
}