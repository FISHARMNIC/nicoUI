/// @brief Create a new button
/// @return New button object
UIButton *UInewButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height, GC normal_color, GC highlight_color, UIText* text, void_fn_ptr callback)
{
    UIButton *button = (UIButton *)malloc(sizeof(UIButton));
    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
    button->gc_normal = normal_color;
    button->gc_highlight = highlight_color;
    button->text = text;
    button->callback = callback;

    UIXnewObject(button, TYPE_BUTTON);

    return button;
}

/// @brief Create a new button with less design options
/// @return New button object
UIButton *UInewButtonQuick(uint32_t x, uint32_t y, uint32_t width, uint32_t height, char *text, void_fn_ptr callback)
{
    GC font = UI_GC_DEFAULT_TEXT;
    UIText* text_obj = UInewText(centerText(x,width,font, text),y + height / 2,text,font);
    UIButton* ret = UInewButton(x, y, width, height, UI_GC_DEFAULT_NORMAL, UI_GC_DEFAULT_HIGHLIGHT, text_obj, callback);
    UIXswapMostRecentObjects();
    return ret;
}

/// @brief Render a single button
/// @param button Object
/// @param highlight 1 or 0, draw as if it was highlighted or not
static inline void UIXrenderButton(UIButton *button, int highlight)
{
    XFillRectangle(
        DW,
        highlight ? button->gc_highlight : button->gc_normal,
        button->x, button->y, button->width, button->height);
}

/// @brief Check all buttons for mouse hover or click
/// @param mouse Motion event holding mouse data
/// @param buttonpress 1 or 0, mouse down or not
void UIXcheckButton(UIButton *button, int mouse_x, int mouse_y, int buttonpress)
{
    if (
        (mouse_x >= button->x) &&
        (mouse_y >= button->y) &&
        (mouse_y <= (button->y + button->height)) &&
        (mouse_x <= (button->x + button->width)))
    {
        UIXrenderButton(button, 1);
        if (buttonpress)
            button->callback();
    }
    else
    {
        UIXrenderButton(button, 0);
    }
}

/// @brief Modify the text of a button. Automatically triggers expose and adjusts length and position
/// @param button Object
/// @param text new text
/// @param length new text length
void UIButton_setText(UIButton *button, char *text, int length)
{
    UIText* obj = button->text;
    UIXText_setText(obj, text, length, 0);
    obj->x = centerText(button->x, button->width, obj->gc, text);
    UIXtriggerExpose();
}