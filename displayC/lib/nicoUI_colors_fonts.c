void __qcolor(XColor* true_color, char* color)
{
    XColor fake;
    XAllocNamedColor(
        display,
        XDefaultColormap(DS),   // colormap
        color,                              // color name
        true_color,                             // closest color possible
        &fake                               // exact color, but we don't care about that
    );
}

GC UIColor_rgb(uint16_t r, uint16_t g, uint16_t b)
{
    XColor color = (XColor){.red = r, .blue = b, .green = g};
    XAllocColor(display, XDefaultColormap(DS), &color);
    XGCValues gc_values = (XGCValues){.foreground = color.pixel};
    return XCreateGC(DW, GCForeground, &gc_values);
}

GC UIColor_named(char* color)
{
    XColor true_color;
    __qcolor(&true_color, color);
    XGCValues gc_values = (XGCValues){.foreground = true_color.pixel};
    gc_values.fill_style = FillOpaqueStippled;
    return XCreateGC(DW, GCForeground, &gc_values);
}

GC UIColoredFont_name(char* font, char* color)
{
    XColor true_color;
    __qcolor(&true_color, color);
    XGCValues gc_values;
    XFontStruct *fontinfo = XLoadQueryFont(display, font); // load font information
    gc_values.font = fontinfo->fid;
    gc_values.foreground = true_color.pixel;
    return XCreateGC(
        display,
        window,
        GCFont+GCForeground, // which components to set
        &gc_values           // where to load from
    );
}
