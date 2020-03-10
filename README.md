# Mizi

![](./media/interface/logo.png)

A simple static website generator written in C++ that takes markdown format as input. 

Inspired from [hundredrabbits/100r.co](https://github.com/hundredrabbits/100r.co)

Created for my website [abstractxan.xyz](https://abstractxan.xyz)

Sample generated repo here : [mizi.netlify.com](https://mizi.netlify.com) 

[![Netlify Status](https://api.netlify.com/api/v1/badges/62460383-615c-4be8-911e-c1513ea806dc/deploy-status)](https://app.netlify.com/sites/mizi/deploys)

## Download and run
- Clone / Download this repository
- Update `src/config.txt`
- Update `src/website.md` 
- Delete files inside `./site` folder
- Run `main.exe` to create site
- Open `index.html`

![](./media/mizi.png)
## Currently supported format:

- A config file for `<head>` , header and footer

``` md
# Category
## Page
### Part
- First
- Second
- Third
<p>Could write in HTML too!</p>
Inline [links!](https://abstractxan.xyz)
Inline images ![images](./media/interface/favicon.ico)

$$$ Seperate Pages
## Seperate Page
### Part
Text
```

## Todo:

``` md
- fix url and image parsing code by split string
- adding classes to images
- fix favicon icon
```
