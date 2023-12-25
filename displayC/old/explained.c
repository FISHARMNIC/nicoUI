// MUST RUN WITH -lX11
// https://www.x.org/releases/current/doc/libX11/libX11/libX11.html
// https://rosettacode.org/wiki/Window_creation/X11

/*
Each screen or monitor is managed by an X server
$DISPLAY env var: points to a local X server, most likely the computer screen
https://askubuntu.com/questions/432255/what-is-the-display-environment-variable
*/

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Display *display;       // server with screens, mouse, keyboard
Window window;          // the window itself
XEvent event;           // how clients are informed
int screen;             // Physical screen like monitor number
XColor    color, dummy; // for colors


char mouse_text[10];

int main()
{
    display = XOpenDisplay(NULL);    // Open connection to X server controlling a display. NULL means $DISPLAY
    screen = DefaultScreen(display); // Reads default screen of the X server. For example, computer screen istelf
    window = XCreateSimpleWindow(    // window inherits attributes from parent window
        display,                     // create it on our display
        RootWindow(display, screen), // parent window = root window
        10,                          // x position
        10,                          // y position
        480,                         // window width
        320,                         // window height
        1,                           // border width
        BlackPixel(display, screen), // Make the border of the window black
        WhitePixel(display, screen)  // Make the background of the window white
    );

    XSelectInput(display, window,
                 ExposureMask | KeyPressMask | PointerMotionMask // report all events in this mask
    );

    
    XAllocNamedColor(
        display,
        DefaultColormap(display, screen),   // colormap
        "red",                              // color name
        &color,                             // closest color possible
        &dummy                              // exact color, but we don't care about that
    );

    XGCValues gc_values;
    XFontStruct *fontinfo = XLoadQueryFont(display, "*courier-bold-r*200*"); // load font information
    gc_values.font = fontinfo->fid;
    gc_values.foreground = color.pixel;
    GC gc_context = XCreateGC(
        display,
        window,
        GCFont+GCForeground, // which components to set
        &gc_values           // where to load from
    );
    
    
    
    XMapWindow(display, window);            // Puts window on screen, generates "expose" event
    

    while (1)
    {
        XNextEvent(display, &event); // Events are queued untill requested by this
        
        if (event.type == MotionNotify)
        {
            XMotionEvent *mouse = (XMotionEvent *)&event; // cast regular event to motion event, giving us acces to x and y

            XClearWindow(display, window);
            XFillRectangle(
                display,                    // display
                window,                     // drawable
                gc_context,                         // graphics context, stores foreground pixel, etc
                mouse->x, mouse->y, 10, 10  // x, y, width, height
            );

            sprintf(mouse_text, "(%03i,%03i)", mouse->x, mouse->y);
            XDrawString(
                display,
                window,
                gc_context,
                10,             // x
                50,             // y
                mouse_text,     // text
                9               // text length
            );
        }
        if (event.type == KeyPress)
            break; // exit the loop
        /*
        Other even types:
            FocusIn, FocusOut, Expose
            ButtonPress, ButtonRelease, MotionNotify
        */
    }

    XCloseDisplay(display); // closes connection and destroys all windows
    return 0;
}