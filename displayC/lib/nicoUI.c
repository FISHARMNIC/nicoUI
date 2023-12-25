#include <X11/Xlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define DW display, window
#define DS display, screen

#define UIblackOnWhite XDefaultGC(DS)

typedef void (*void_fn_ptr)();

/// @brief Specifies a general UI element;
typedef struct
{
    int type;
    void *ptr;
} UIObject;

/// @brief Different object types in UIObject
enum
{
    TYPE_BUTTON,
    TYPE_INPUT,
    TYPE_TEXT
};

#define MAXOBJECTS 255 // Max number of UI elements allowed
UIObject *UIallObjects[MAXOBJECTS];
int __allObjectsLoadIndex = 0;

Display *display;
Window window;
int screen;

#include "nicoUI_object_typedefs.h"

int UIXKeypressLocked = 0;
UIInput *UIXLockedInput;
void UIXKeypressLockOnInput(UIInput *input);

GC UI_GC_DEFAULT_TEXT;
GC UI_GC_DEFAULT_NORMAL;
GC UI_GC_DEFAULT_HIGHLIGHT;
GC UI_GC_DEFAULT_ERROR;
GC UI_GC_DEFAULT_SUCCESS;

#include "nicoUI_util.c"
#include "nicoUI_colors_fonts.c"
#include "nicoUI_text.c"
#include "nicoUI_button.c"
#include "nicoUI_textInput.c"
#include "nicoUI_object_handle.c"

UIInput *lockedInput;

void UIinitialize(Display *disp, Window wind, int scr)
{
    display = disp;
    window = wind;
    screen = scr;

    UI_GC_DEFAULT_NORMAL = UIColor_named("gray");
    UI_GC_DEFAULT_TEXT = UIColoredFont_name("6x10", "black");
    UI_GC_DEFAULT_HIGHLIGHT = UIColor_named("lightgray");
    UI_GC_DEFAULT_ERROR = UIColor_named("red");
    UI_GC_DEFAULT_SUCCESS = UIColor_named("green");
}

void UIquickInit(int width, int height)
{
    display = XOpenDisplay(NULL);
    window = XCreateSimpleWindow(display, XRootWindow(DS), 10, 10, width, height, 1, XBlackPixel(DS), XWhitePixel(DS));
    screen = DefaultScreen(display);

    UIinitialize(display, window, screen);

    XSelectInput(DW, ExposureMask | KeyPressMask | PointerMotionMask | ButtonPressMask);
}

int UIrender()
{
    XMapWindow(DW); // show on screen

    XEvent event;
    while (1)
    {
        XNextEvent(display, &event);

        if (event.type == Expose)
        {
            UIXRenderAllObjects();
        }
        if ((event.type == MotionNotify) && !UIXKeypressLocked)
        {
            XMotionEvent *mouse = (XMotionEvent *)&event;
            UIXCheckAllObjects(mouse->x, mouse->y, 0);
        }
        if (event.type == ButtonPress)
        {
            XMotionEvent *mouse = (XMotionEvent *)&event;
            UIXCheckAllObjects(mouse->x, mouse->y, 1);
        }
        if (event.type == KeyPress)
        {
            XKeyPressedEvent *kb = (XKeyPressedEvent *)&event;
            int keycode = XLookupKeysym(kb, 0);
            int keycodeShort = (uint8_t)keycode;
            char key = XKeysymToString(keycode)[0]; // convert key press to char
            if (UIXKeypressLocked)
            {
                UIXGetCharIntoLockedInput(keycodeShort, key);
            }
        }
    }

    XCloseDisplay(display); // closes connection and destroys all windows
    return 0;
}