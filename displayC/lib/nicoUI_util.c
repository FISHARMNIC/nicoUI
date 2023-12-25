
int textLengthFromGC(GC gc, char* string)
{
    return XTextWidth(XQueryFont(display,XGContextFromGC(gc)), string, strlen(string));
}

int centerText(int x, int width, GC font_type, char* text)
{
    return x + (width - textLengthFromGC(font_type, text)) / 2;
}

int centerTextFromLen(int x, int width, GC font_type, int textLength)
{
    return x + (width - textLengthFromGC(font_type, "0") * textLength) / 2;
}

void UIXtriggerExpose()
{
    XEvent event = (XEvent){.type = Expose};
    XSendEvent(DW, False, ExposureMask, &event);
}

void UIXnewObject(void* object, int type)
{
    UIObject *obj = (UIObject *)malloc(sizeof(UIObject));
    obj->ptr = object;
    obj->type = type;
    UIallObjects[__allObjectsLoadIndex++] = obj;
}

void UIXswapMostRecentObjects()
{
    UIObject *obj = UIallObjects[__allObjectsLoadIndex - 1];
    UIallObjects[__allObjectsLoadIndex - 1] = UIallObjects[__allObjectsLoadIndex - 2];
    UIallObjects[__allObjectsLoadIndex - 2] = obj;
}