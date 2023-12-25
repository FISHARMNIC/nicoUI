void UIXRenderAllObjects()
{

    for (int i = 0; i < __allObjectsLoadIndex; i++)
    {
        UIObject *e = UIallObjects[i];
        switch (e->type)
        {
        case TYPE_BUTTON:
        {
            UIXrenderButton((UIButton *)e->ptr, 0);
            break;
        };
        case TYPE_INPUT:
        {
            UIXrenderInput((UIInput *)e->ptr, 0, 0);
        };
        case TYPE_TEXT:
        {
            UIXrenderText((UIText *)e->ptr);
        }
        }
    }
}

void UIXCheckAllObjects(int mouse_x, int mouse_y, int click)
{
    for (int i = 0; i < __allObjectsLoadIndex; i++)
    {
        UIObject *e = UIallObjects[i];
        switch (e->type)
        {
        case TYPE_BUTTON:
        {
            UIXcheckButton((UIButton *)e->ptr, mouse_x, mouse_y, click);
            break;
        };
        case TYPE_INPUT:
        {
            UIXcheckInput((UIInput *)e->ptr, mouse_x, mouse_y, click);
        };
        case TYPE_TEXT:
        {
            UIXcheckText((UIText *)e->ptr);
        };
        }
    }
}

void UIXKeypressLockOnInput(UIInput *input)
{
    UIXKeypressLocked = 1;
    UIXLockedInput = input;
}

void UIXGetCharIntoLockedInput(int keycode, char key)
{
    char *buffer = UIXLockedInput->buffer;
    int len = strlen(buffer);
    if (keycode == 8) // backspace
    {
        buffer[len - 1] = 0;
        UIXrenderInput(UIXLockedInput, 1, 0);
    }
    else if (keycode == 13) // newline
    {
        UIXKeypressLocked = 0;
        UIXrenderInput(UIXLockedInput, 1, 0);
    }
    else if (len < UIXLockedInput->bufferLength)
    {
        if (keycode == 32) // space
        {
            buffer[len] = ' ';
        }
        else
        {
            buffer[len] = key;
        }
        UIXrenderInput(UIXLockedInput, 1, 0);
    }
    else
    {
        UIXrenderInput(UIXLockedInput, 1, 1);
    }
}