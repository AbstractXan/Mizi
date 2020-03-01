#include<string>
#include<iostream>
#include<fstream>
using namespace std;

string html_head(string text){
    return "<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta name='description' content='AbstractXan'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta name='twitter:card' content='summary'><meta name='twitter:site' content='@abstractxan'><meta name='twitter:title' content='AbstractXan'><meta name='twitter:description' content='AbstractXan creates art , games and open source tools.'><meta name='twitter:creator' content='@abstractxan'><meta name='twitter:image' content='../media/interface/logo.png'><meta property='og:title' content='AbstractXan'><meta property='og:site_name' content='AbstractXan'><title>AbstractXan — "+text+"</title><link rel='stylesheet' type='text/css' href='../links/main.css'></head><body class='"+text+"'>";
}
string html_header = "<header><a id='logo' href='home.html'><img src='../media/interface/logo.png' alt='AbstractXan' ></a></header>";

string html_footer = "<footer>Abstractxan Ⓒ 2020<p>Never miss an update</p><form action='https://tinyletter.com/abstractxan' method='post' target='popupwindow' onsubmit='window.open(\'https://tinyletter.com/abstractxan\', \'popupwindow\', \'scrollbars=yes,width=800,height=600\');return true'><input type='email' value='' name='EMAIL' class='email' placeholder='email@address.com' required=''><input type='submit' value='Subscribe' name='subscribe' class='button'></form></footer></body></html>";

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

// Debug
// void printContent(Category * cats[],int count){
//     for(int i=0; i<count;i++){
//         Category tempCat = *cats[i];
//         cout << tempCat.name << endl;

//         for(int pageno=0;pageno<tempCat.pageCount;pageno++){
//             Page tempPage = *tempCat.pages[pageno];
//             cout << "\t" << tempPage.title << endl;
            
//             for(int partno=0;partno<tempPage.partsCount;partno++){
//                 cout << "\t\t" << tempPage.partName[partno]<<endl;
//                 cout << "\t\t" << tempPage.partDesc[partno]<<endl;
//             }
//         }
//     }
// }

//Prints errorline
void printError(int linenumber, string text){
    cout<<"Error at line " << linenumber << ". " << text << endl;
}

void buildHome(Category * categories[], int categories_length){
    ofstream htmlHome;
    htmlHome.open("../site/home.html");
    htmlHome << html_head("home");
    htmlHome << html_header;
    htmlHome << "<main class='home'>";

    for(int i=0;i<categories_length;i++){
        Category * category = categories[i];
        htmlHome << "<h2>"<< category->name << "</h2>";
        htmlHome << "<ul>";
        for(int j=0; j< category->pageCount;j++){
            Page *page = category->pages[j];
            string page_name = page->title;
            string page_index = toLowerCase(page_name);
            htmlHome << "<li><a href='" << page_index << ".html'>" << page_name << "</a></li>";
        }
        htmlHome << "</ul>";
    }

    htmlHome << "<hr/>";
    htmlHome << "</main>";
    htmlHome << html_footer;
    htmlHome.close();
}

void buildPage(Page * page){
    ofstream htmlPage;
    string filename = toLowerCase(page->title);
    string filepath = "../site/"+filename+".html";
    htmlPage.open(filepath.c_str());
    htmlPage << html_head(page->title);
    htmlPage << html_header;
    htmlPage << "<main class='page'>";
    htmlPage << "<h1>" << page->title << "</h1>";
    
    if(page->partsCount >=3 ){
    htmlPage << "<ul class='jump'>";
        for(int i=0;i<page->partsCount;i++){
            string part_name = page->partName[i];
            string part_index = toLowerCase(part_name);
            htmlPage << "<li><a href='#"<<part_index<<"'>"<<part_name<<"</a></li>";
        }
        htmlPage << "</ul>";
    }

    for(int i=0;i<page->partsCount;i++){
        string part_name = page->partName[i];
        string part_desc = page->partDesc[i];
        string part_index = toLowerCase(part_name);
        htmlPage << "<h2 id='" << part_index << "'>" << part_name << "</h2>";
        htmlPage << part_desc;
    }

    htmlPage << "<hr/>";
    htmlPage << "</main>";
    htmlPage << html_footer;
    htmlPage.close();
}

void createSite(Category * cats[],int count){

    buildHome(cats,count);
    for(int i=0; i<count;i++){
        Category tempCat = *cats[i];

        for(int pageno=0;pageno<tempCat.pageCount;pageno++){
            Page * tempPage = tempCat.pages[pageno];
            buildPage(tempPage);
        }
    }
}