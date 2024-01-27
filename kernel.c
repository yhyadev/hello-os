#include <stdbool.h>
#include <stddef.h>

#include "screen.h"
#include "vga.h"

size_t strlen(const char *string) {
    size_t len = 0;

    while (string[len]) len++;

    return len;
}

void write_string(const char *string) {
    for (size_t i = 0; i < strlen(string); i++) {
        screen_write(VGA_COLOR_WHITE, string[i]);
    }
}

void kmain(void) {
    screen_init();

    while (true) {
        screen_clear(VGA_COLOR_BLACK);

        write_string("Hello World");
    }
}
