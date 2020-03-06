#include<fstream>
#include"reader.h"

using namespace std;

void createSite(){
    Category ** cats;
    int categoryCount = 0;
    cats = createCategories(&categoryCount);
    cout << "Categories found: " << categoryCount << endl;

        
    //Debug categories
    //printContent(cats,categoryCount);

    buildHome(cats,categoryCount);
    for(int i=0; i<categoryCount;i++){
        Category tempCat = *cats[i];

        for(int pageno=0;pageno<tempCat.pageCount;pageno++){
            Page * tempPage = tempCat.pages[pageno];
            buildPage(tempPage);
        }
    }
}

int main(){ 
    createSite();
    return 0;
}