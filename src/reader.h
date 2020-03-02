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
    for(unsigned int i=0;i<text.size();i++){
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

Category ** createCategories(int * categoryCount){

    string line;
    int lineNo=0;

    Category * currentCategory; 
    Page * currentPage;   
    bool uList = false;
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

            //Removing unwanted spaces
            while(line[i]==' '){
                i++;
            }

            // Headings
            if (line[i]=='#'){
                while(line[i]=='#'){
                    hashcount++;
                    i++;
                }

                // Category
                if(hashcount==1){
                    currentCategory = createCategory(line.substr(i+1,line.size()-i),*categoryCount);
                    (*categoryCount)++;
                    uList = false;
                }

                // Page
                else if(hashcount==2){   
                    if (currentCategory->name.empty()){
                        printError(lineNo,"No Category assigned!");
                        return 0;
                    }
                    currentPage = createPage(line.substr(i+1,line.size()-i));
                    addPage(currentCategory,currentPage);
                    uList = false;
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
                    currentPartDesc = "<p>";
                    uList = false;
                }
            } 
            else //No headings
            {
                // Error
                if(currentPartName==""||currentPage->title.empty()){
                    printError(lineNo,"No Part assigned!");
                    return 0;
                }

                // Ul
                if(line[i]=='-'){
                    i++;
                    // If not in a ul 
                    if(uList==false){
                        currentPartDesc += "<ul>";
                        uList=true;
                    }

                    currentPartDesc += "<li>";
                    currentPartDesc += line.substr(i+1,line.size()-i);
                    currentPartDesc += "</li>";

                } else { // If list doesn't continue
                    if(uList==true){
                        uList=false;
                        currentPartDesc += "</ul>";
                    }

                    currentPartDesc+=line;
                    currentPartDesc+="";
                }

                // For <ul> continuing to next part of the page, Every 'part name' has an extra </ul> to keep a check.
                // Refer to build page function

                // Update if page exists, add to current part i.e. (partsCount - 1)
                if (currentPage->title != "")
                    currentPage->partDesc[(currentPage->partsCount)-1]=currentPartDesc;
            }
        }
        mdFile.close();
    } else {
        cout << "Unable to open file"<<endl; }
    return Categories;
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
        htmlPage << "</ul><h2 id='" << part_index << "'>" << part_name << "</h2>"; // Extra </ul> to keep a check on overflowing <ul>
        htmlPage << part_desc;
    }

    htmlPage << "<hr/>";
    htmlPage << "</main>";
    htmlPage << html_footer;
    htmlPage.close();
}

void createSite(){

    Category ** cats;
    int categoryCount = 0;
    cats = createCategories(&categoryCount);
    cout << "Categories found: " << categoryCount << endl;

        
    //Debug Refer
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