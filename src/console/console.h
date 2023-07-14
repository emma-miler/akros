struct akr_console_t;
typedef void (*akr_console_flush_f)(void *This);

typedef struct
{
    akr_console_flush_f flush;
} akr_console_t;
extern akr_console_t* Console;
