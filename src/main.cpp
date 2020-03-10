#include<fstream>
#include"reader.cpp"

using namespace std;

void createSite(){
    Category ** cats;
    int categoryCount = 0;
    cats = createCategories(&categoryCount);
    cout << "Categories found: " << categoryCount << endl;

    conf = configParser();
    html_header = "<header>"+conf->header+"</header>";
    html_footer = "<footer><p>"+conf->footer+"</p></footer></body></html>";
    //Debug categories
    //printContent(cats,categoryCount);

    buildHome(cats,categoryCount);
    for(int i=0; i<=categoryCount;i++){ //Build all pages including seperate pages
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