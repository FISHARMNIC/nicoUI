typedef struct
{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    GC gc_normal;
    GC gc_highlight;

    char *buffer;
    GC gc_font;
    GC gc_bufferFull;

    uint32_t text_x;
    uint32_t text_y;

    uint32_t bufferLength;
} UIInput;

typedef struct
{
    uint32_t x;
    uint32_t y;

    char* buffer;
    int bufferLength;

    GC gc;
} UIText;

typedef struct
{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;

    GC gc_normal; // normal graphics context
    GC gc_highlight;     // graphics context when highlighted

    UIText *text;      // button text

    void_fn_ptr callback; // function called when clicked
} UIButton;