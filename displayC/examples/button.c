#include "../lib/nicoUI.c"
#include <stdio.h>
#include <stdlib.h>

void myButtonCallback();

UIButton* myButton;

char clickText[12];
int timesClicked = 0;

int main()
{
    UIquickInit(480, 320);

    //myButton = UInewButton(200,140,80,40,UIColor_named("gray"),UIColor_named("lightgray"),"Clicked 000",UIColoredFont_name("6x10", "black"),myButtonCallback);
    myButton = UInewButtonQuick(200, 140, 80, 40, "Clicked 000", myButtonCallback);
    
    return UIrender();
}

void myButtonCallback()
{
    sprintf(clickText, "Clicked %03i", ++timesClicked);
    UIButton_setText(myButton, clickText, 11);
}