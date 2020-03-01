#include<string>
#include<iostream>
using namespace std;

char getLower(char c){
    if (c >= 'A' && c <='Z')
        return c-('Z'-'z');
    return c;
}

string toLowerCase(string text){
    for(int i=0;i<text.size();i++){
        if (text[i]=='\0')
            break;
        else if(text[i]==' ')
            text[i]='_';
        else 
            text[i] = getLower(text[i]);
    }
    return text;        
}

struct Page{
    string title;
    int partsCount;
    string partName[32];
    string partDesc[32];
};

Page * createPage(string title){
    Page * newpage = new Page;
    newpage->title=title;
    newpage->partsCount=0;
    return newpage;
}

void addPart(Page * page, string name){
    page->partName[page->partsCount]= name;
    page->partsCount++;
}

void buildPage(Page * page){

}
struct Category{
    string name;
    int pageCount;
    Page * pages[32];
};


struct Category * Categories[16];

Category * createCategory(string name,int count){
    Category * newCategory = new Category;
    newCategory->name = name;
    newCategory->pageCount = 0;
    Categories[count]=newCategory;
    return newCategory;
}
void addPage(Category * category, Page * page){
    category->pages[category->pageCount] = page;
    category->pageCount++;
}


void printContent(Category * cats[],int count){
    for(int i=0; i<count;i++){
        Category tempCat = *cats[i];
        cout << tempCat.name << endl;

        for(int pageno=0;pageno<tempCat.pageCount;pageno++){
            Page tempPage = *tempCat.pages[pageno];
            cout << "\t" << tempPage.title << endl;
            
            for(int partno=0;partno<tempPage.partsCount;partno++){
                cout << "\t\t" << tempPage.partName[partno]<<endl;
                cout << "\t\t" << tempPage.partDesc[partno]<<endl;
            }
        }
    }
}

//Prints errorline
void printError(int linenumber, string text){
    cout<<"Error at line " << linenumber << ". " << text << endl;
}
