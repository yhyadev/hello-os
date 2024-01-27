#include <stdint.h>
#include <stddef.h>

#include "screen.h"
#include "vga.h"

uint16_t *screen_buffer = VGA_BUFFER_ADDRESS;
size_t screen_current_row;
size_t screen_current_column;

uint16_t vga_entry(int color, const char c) {
    return c | color << 8;
}

void screen_init(void) {
    screen_clear(VGA_COLOR_BLACK);
};

void screen_clear(int color) {
    screen_current_column = 0;
    screen_current_row = 0;

    for (size_t y = 0; y < VGA_BUFFER_HEIGHT; y++) {
            for (size_t x = 0; x < VGA_BUFFER_WIDTH; x++) {
                const size_t index = y * VGA_BUFFER_WIDTH + x;
                screen_buffer[index] = vga_entry(color, ' ');
            }
        }
    };

void screen_write(int color, char c) {
    const size_t index = screen_current_row * VGA_BUFFER_WIDTH + screen_current_column;
    screen_buffer[index] = vga_entry(c, color);

    if (++screen_current_column == VGA_BUFFER_WIDTH) {
        screen_current_column = 0;

        if (++screen_current_row == VGA_BUFFER_HEIGHT) {
            screen_current_row = 0;
        }
    }
};
