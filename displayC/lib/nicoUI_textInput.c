UIInput *UInewInput(int x, int y, int width, int height, GC gc_normal, GC gc_highlight, char *buffer, int bufferLength, GC font_type, GC gc_bufferFull)
{
    UIInput *input = (UIInput *)malloc(sizeof(UIInput));
    input->x = x;
    input->y = y;
    input->width = width;
    input->height = height;
    input->gc_normal = gc_normal;
    input->gc_highlight = gc_highlight;
    input->gc_bufferFull = gc_bufferFull;
    input->buffer = buffer;
    input->bufferLength = bufferLength;
    input->gc_font = font_type;
    input->text_x = centerTextFromLen(x, width, font_type, bufferLength);
    input->text_y = y + height / 2;

    UIXnewObject(input, TYPE_INPUT);

    return input;
}

UIInput *UInewInputQuick(int x, int y, int width, int height, char* buffer, int bufferLength)
{
    return UInewInput(x, y, width, height, UI_GC_DEFAULT_NORMAL, UI_GC_DEFAULT_HIGHLIGHT, buffer, bufferLength, UI_GC_DEFAULT_TEXT, UI_GC_DEFAULT_ERROR);
}

static inline void UIXrenderInput(UIInput *input, int highlight, int bufferFull)
{
    XFillRectangle(
        DW,
        bufferFull? input-> gc_bufferFull : (highlight? input->gc_highlight : input->gc_normal),
        input->x, input->y, input->width, input->height);
    XFillRectangle(
        DW,
        input->gc_font,
        input->x, input->height + input->y - 5, input->width, 3);
    XDrawString(
        DW,
        input->gc_font,
        input->text_x,
        input->text_y,
        input->buffer,
        input->bufferLength);
}

void UIXcheckInput(UIInput *input, int mouse_x, int mouse_y, int buttonpress)
{
    if (
        (mouse_x >= input->x) &&
        (mouse_y >= input->y) &&
        (mouse_y <= (input->y + input->height)) &&
        (mouse_x <= (input->x + input->width)))
    {
        UIXrenderInput(input, 1,0 );
        if(buttonpress)
            UIXKeypressLockOnInput(input);
    } else {
        UIXrenderInput(input, 0,0 );
    }
}