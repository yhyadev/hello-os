#include <stdbool.h>
#include <stddef.h>

#include "screen.h"
#include "vga.h"

size_t strlen(const char *string) {
    size_t len = 0;

    while (string[len]) len++;

    return len;
}

void write_string(Screen *screen, const char *string) {
    unsigned char color_code = get_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE);

    for (size_t i = 0; i < strlen(string); i++) {
        screen_write(screen, color_code, string[i]);
    }
}

void kmain(void) {
    Screen screen = screen_init((volatile ScreenChar *)VGA_BUFFER_ADDRESS);

    write_string(&screen, "Hello World");

    while (true) {}
}
