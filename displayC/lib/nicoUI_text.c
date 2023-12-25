UIText* UInewText(uint32_t x, uint32_t y, char* buffer, GC gc)
{
    UIText *text = (UIText *)malloc(sizeof(UIText));
    
    text->x = x;
    text->y = y;
    text->gc = gc;
    text->buffer = buffer;
    text->bufferLength = strlen(buffer);

    UIXnewObject(text, TYPE_TEXT);

    return text;
}

UIText* UInewTextQuick(uint32_t x, uint32_t y, char* buffer)
{
    return UInewText(x, y, buffer, UI_GC_DEFAULT_TEXT);
}

void UIXrenderText(UIText* text)
{
    XDrawString(
        DW,
        text->gc,
        text->x,
        text->y,
        text->buffer,
        text->bufferLength);
}

void UIXcheckText(UIText* text)
{
    UIXrenderText(text);
}

void UIXText_setText(UIText *obj, char *text, int length, int expose)
{
    obj->buffer = text;
    obj->bufferLength = length;
    if(expose) 
        UIXtriggerExpose();
}

static inline void UIText_setText(UIText *obj, char *text, int length)
{
    UIXText_setText(obj, text, length, 1);
}