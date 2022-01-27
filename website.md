# Mizi
## About
###  
This site was generated using this file: [website.md](https://raw.githubusercontent.com/AbstractXan/Mizi/master/src/website.md)

[Read more](https://github.com/abstractxan/mizi) about Mizi

# $$$ 
## separate
### 
This is a separate page
## separate2
###  
This is separate page2

# Features
## HTML
### Html &lt; p &gt; tag
<p>This is a paragraph</p>

## Index
### First
Lorem Ipsum
### Second
Dolor sit amet
### Third
Consectetur adipiscing elit
Hell!

## Unordered List
### UL
- First
- Second
- Third
### UL Overflow Check
- Above text should be heading 

## Links
### Simple
[link](https://www.abstractxan.xyz)
### Inline
Text [link](https://abstractxan.xyz) text
### Multiple
Text [link](https://abstractxan.xyz) text [link](https://abstractxan.xyz) text
### Errors
[broken text (https://abstractxan.xyz)

[broken text [text](https://abstractxan.xyz)

[broken link](https://abstractxan.xyz [normal link](https://www.abstractxan.xyz)

[broken link]

[nested [links] (https://abstractxan.xyz)](https://google.com)

## Images
### Optional alt text
![](../media/interface/favicon.ico)
### Single
![image](../media/interface/favicon.ico)
### Inline
Text ![image](../media/interface/favicon.ico) Text
### Multiple
![image](../media/interface/favicon.ico) ![image](../media/interface/favicon.ico)
### Errors
![brokenImageText (../media/interface/favicon.ico)
![brokenImageLink]

## SeparatePages
### 
Separate pages are not shown on home page
- [Separate page](separate.html)
- [Separate page2](separate2.html)


## Templates
### Intro
Templates are defined in [template.conf](https://raw.githubusercontent.com/AbstractXan/Mizi/master/src/template.conf) file and used in [website.md](https://raw.githubusercontent.com/AbstractXan/Mizi/master/src/website.md)

### Single Line No Argument
{{SingleLineTemplateNoArg}}

### Single Line One Arg
{{variable = asdfasf}}
{{SingleLineTemplateOneArg var=variable }}
{{SingleLineTemplateOneArg var=value2}}

### Single Line Multiple Arg
{{SingleLineTemplateMultipleArg var1=value1 var2=value2}}

### Multi Line No Arg
{{MultiLineTemplateNoArg}}

### Multi Line One Arg
{{MultiLineTemplateOneArg var=value1}}

### Multi Line Multple Arg
{{MultiLineTemplateMultipleArg var1=value1 var2=value2}}

### Bad Syntax Examples
- {{NonexistentTemplate}}
- {{SingleLineTemplateNoArg} <- Wrong Syntax

# {{TemplateHeader}}
## {{TemplatePage}}
### {{TemplateSection}}
Text