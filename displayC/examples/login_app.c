#include "../lib/nicoUI.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UIInput* username_input;
UIInput* password_input;

UIText* username_text;
UIText* password_text;

UIButton* login_button;

char usernameBuffer[20];
char passwordBuffer[20];

void login_callback()
{
   if(strcmp(usernameBuffer, "bob") == 0 && strcmp(passwordBuffer, "123") == 0)
    {
        login_button->gc_normal = UI_GC_DEFAULT_SUCCESS;
        login_button->gc_highlight = UI_GC_DEFAULT_SUCCESS;
    } else 
    {
        login_button->gc_normal = UI_GC_DEFAULT_ERROR;
        login_button->gc_highlight = UI_GC_DEFAULT_ERROR;
    }
    UIXtriggerExpose();
}

int main()
{
    UIquickInit(480, 320);
    username_input = UInewInputQuick(10, 10, 120, 20, usernameBuffer, 20);
    username_text = UInewTextQuick(140, 20, "username");
    
    password_input = UInewInputQuick(10, 40, 120, 20, passwordBuffer, 20);
    password_text = UInewTextQuick(140, 50, "password");

    login_button = UInewButtonQuick(10, 70, 50, 20, "login", login_callback);
    return UIrender();
}