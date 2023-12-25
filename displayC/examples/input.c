#include "../lib/nicoUI.c"
#include <stdio.h>
#include <stdlib.h>

UIInput* myInput;
char inputBuffer[20];

int main()
{
    UIquickInit(480, 320);

    myInput = UInewInputQuick(180, 140,120, 20,inputBuffer, 20);
    
    return UIrender();
}
