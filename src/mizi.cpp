#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include"helpers.cpp"
using namespace std;

struct Config{
    string shortcut_icon;
    string icon;
    string name;
    string description;
    string twitter_creator;
    string header;
    string footer;
};

Config * configParser(){
    Config * conf = new Config;
    ifstream configFile ("config.txt");
    if (configFile.is_open())
    {
    string line;
    while( getline(configFile, line) ){
        istringstream is_line(line);
        string key;
        if(getline(is_line, key, '=')){
            string value;
            if(getline(is_line, value)){ 
                if(key=="shortcut_icon"){ conf->shortcut_icon=value;
                } else if(key=="icon"){ conf->icon=value;
                } else if(key=="name"){ conf->name=value;
                } else if(key=="description"){ conf->description=value;
                } else if(key=="creator"){ conf->twitter_creator=value;
                } else if(key=="header"){ conf->header=value;
                } else if(key=="footer"){ conf->footer=value;
                } else {
                    cout << "Config file syntax error." << endl;
                }
                }
            }
        }
    }
    configFile.close();
    return conf;    
}

Config * conf;
string html_head(string text){
    return "<!DOCTYPE html><html lang='en'><head><link rel='shortcut icon' href='"+ conf->shortcut_icon +"' type='image/x-icon'><link rel='icon' href='"+conf->icon+"' type='image/x-icon'><meta charset='utf-8'><meta name='description' content='"+conf->description+"'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta name='twitter:card' content='summary'><meta name='twitter:site' content='"+conf->name+"'><meta name='twitter:title' content='"+conf->name+"'><meta name='twitter:description' content='"+conf->description+"'><meta name='twitter:creator' content='@"+conf->twitter_creator+"'><meta name='twitter:image' content='"+conf->icon+"'><meta property='og:title' content='"+conf->name+"'><meta property='og:site_name' content='"+conf->name+"'><title> "+conf->name+" - "+text+"</title><link rel='stylesheet' type='text/css' href='../links/main.css'></head><body class='"+text+"'>";
}
string html_header = "";
string html_footer = "";

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
struct Page * SeparatePages[20];

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
void printContent(Category * cats[],int count){
    for(int i=0; i<=count;i++){
        Category tempCat = *cats[i];
        cout << tempCat.name << endl;

        for(int pageno=0;pageno<tempCat.pageCount;pageno++){
            Page tempPage = *tempCat.pages[pageno];
            cout << "\t |" << tempPage.title << endl;
            
            for(int partno=0;partno<tempPage.partsCount;partno++){
                cout << "\t\t |" << tempPage.partName[partno]<<endl;
                cout << "\t\t |" << tempPage.partDesc[partno]<<endl;
            }
        }
    }
}

//Prints errorline
void printError(int linenumber, string text){
    cout<<"Error at line " << linenumber << ". " << text << endl;
}

//  [urlText](url) ->  <a href='url'>urlText</a>
// ![altText](image) -> <img src='' alt=''> 
string parseLinks(string text){
    unsigned int index = 0;
    string newText = "";
    string urlText = "";
    string url = "";
    bool isImage = false;

        for(;index<text.size();){
            // Enter into linking
            // ![ -> image flag true
            if(text[index]=='!' && text[index+1]=='['){
                isImage = true;
                index++;
                continue;

                //
            }else if(text[index]=='['){
                
                // Crude implementation for images
                if(index>=1 && text[index-1]=='!'){
                    isImage = true;
                } else {
                    isImage = false;
                }

                index++;
                //Loop through urltext
                while(index<text.size() && text[index]!=']'){
                    
                    //Broken [text [text](link) case
                    if(text[index]=='['){
                        newText += '[' + urlText;
                        urlText = "";
                        index++;
                    }

                    urlText += text[index];
                    index++;
                }

                // EndofUrlText
                // [urltext]
                if(text[index]==']'&&index<text.size())
                {
                    index++;
                    if(text[index]=='('&&index<text.size()){
                        index++; 
                        //Continue
                        while(index<text.size() && text[index]!=')'){
                            
                            // Error [link](abc.com [link](abc.com)
                            if(text[index]=='['){
                                newText += '[' + urlText + "](" + url;
                                urlText = "";
                                break;
                            }
                            url += text[index];
                            index++;
                        }

                        // Complete parsing
                        if(text[index]==')'&&index<text.size()){

                            if(isImage){
                                index++;
                                newText += "<img src='" + url + "' alt='" + urlText + "'>";
                            } else{
                                index++;
                                newText += " <a href='" + url +"'>" + urlText +"</a>";
                            }
                            url = "";
                            urlText = "";
                            isImage = false;
                            continue;
                        }

                        if(index==text.size()){
                            newText += '[' + urlText + "]("+ url;
                            continue;
                        }
                    }
                    else{
                        newText += '[' + urlText + ']';
                        urlText = "";
                        continue;
                    }
                } else {
                    newText += '['+ urlText;
                    urlText = "";
                    continue;
                }
            } else {
                newText += text[index];
                index++;
            }
        }
    return newText;
}

Category ** createCategories(int * categoryCount, string filename){

    string line;
    int lineNo=0;

    Category * currentCategory; 
    Page * currentPage = NULL;   
    bool uList = false;
    string currentPartName = "";
    string currentPartDesc = "";

    //Category for separate pages
    Category * seperateCategory = createCategory("SeperatePages",0);
    
    ifstream mdFile (filename);
    
    if (mdFile.is_open())
    {
        while ( getline (mdFile,line) )
        {
            lineNo++;
            int hashcount=0;
            int i=0;
            
            if(line == ""){
                currentPartDesc+="<br>";
                continue;
            }

            line = parseLinks(line);
            
            //Removing unwanted spaces
            while(line[i]==' '){
                i++;
            }

            if(line[i] == '$' && line[i+1] == '$' && line[i+2] == '$'){
                //Seperate page
                currentCategory = seperateCategory;
                uList = false;
                continue;
            }
            
            // Headings
            if (line[i]=='#'){
                while(line[i]=='#'){
                    hashcount++;
                    i++;
                }

                // Category
                if(hashcount==1){
                    (*categoryCount)++; // Categories stored from 1 onwards , categories[0] for separate pages 
                    currentCategory = createCategory(line.substr(i+1,line.size()-i),*categoryCount);
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
            else{    //No headings: Plaintext
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
                    currentPartDesc += "<p>"+line+"</p>";
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

void buildHome(Category * categories[], int categories_length, string path){
    ofstream htmlHome;
    htmlHome.open(path+"/home.html");
    htmlHome << html_head("Home");
    htmlHome << html_header;
    htmlHome << "<main class='home'>";

    for(int i=1;i<=categories_length;i++){
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

void buildPage(Page * page,string path){
    ofstream htmlPage;
    string filename = toLowerCase(page->title);
    string filepath = path+filename+".html";
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

void createSite(string filename, string path){
    Category ** cats;
    int categoryCount = 0;
    cats = createCategories(&categoryCount, filename);
    cout << "Categories found: " << categoryCount << endl;

    conf = configParser();
    html_header = "<header>"+conf->header+"</header>";
    html_footer = "<footer><p>"+conf->footer+"</p></footer></body></html>";
    //Debug categories
    //printContent(cats,categoryCount);

    buildHome(cats,categoryCount,path);
    for(int i=0; i<=categoryCount;i++){ //Build all pages including seperate pages
        Category tempCat = *cats[i];

        for(int pageno=0;pageno<tempCat.pageCount;pageno++){
            Page * tempPage = tempCat.pages[pageno];
            buildPage(tempPage,path);
        }
    }
}
