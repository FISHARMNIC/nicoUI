# nicoUI
* UI library for X11. To run on macos use [XQuartz](https://www.xquartz.org)
* Currently supports
    * Buttons
    * Inputs
    * Text
* Meant to provide an easy-access UI library for, as opposed to things like GTK
* See `examples` for some simple demos


<img width="508" alt="Screen Shot 2023-12-24 at 4 50 34 PM" src="https://github.com/FISHARMNIC/nicoUI/assets/73864341/653038b5-de5e-45ec-8927-64c3d4293b74">
<img width="508" alt="Screen Shot 2023-12-24 at 4 55 43 PM" src="https://github.com/FISHARMNIC/nicoUI/assets/73864341/a3a257ca-d5e4-43ac-92c6-07576c33718a">

Code for button counter above. No other library installation necessary (except nicoUI)
```C
#include "../lib/nicoUI.c"
#include <stdio.h>
#include <stdlib.h>

void myButtonCallback();

UIButton* myButton;

char clickText[12];
int timesClicked = 0;

int main()
{
    UIquickInit(480, 320); // create screen with width and height

    myButton = UInewButtonQuick(
        200,                // x
        140,                // y
        80,                 // width
        40,                 // height
        "Clicked 000",      // text
        myButtonCallback    // callback
    );
    
    return UIrender(); // show the window
}

void myButtonCallback()
{
    sprintf(clickText, "Clicked %03i", ++timesClicked);
    UIButton_setText(myButton, clickText, 11); // change the text
}
```
