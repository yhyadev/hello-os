#pragma once

#include <stddef.h>

#include "vga.h"

unsigned char get_color(unsigned char background, unsigned char foreground);

typedef struct {
    unsigned char ascii_character;
    unsigned char color_code;
} ScreenChar;

typedef struct {
    volatile ScreenChar *characters;
    size_t current_column;
    size_t current_row;
} ScreenBuffer;

typedef struct {
    ScreenBuffer buffer;
} Screen;

Screen screen_init(volatile ScreenChar *characters);
void screen_clear(Screen *screen, unsigned char color_code);
void screen_write(Screen *screen, unsigned char color_code, unsigned char c);
