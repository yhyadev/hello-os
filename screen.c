#include <stddef.h>

#include "screen.h"
#include "vga.h"

unsigned char get_color(unsigned char background, unsigned char foreground) {
    return background << 4 | foreground;
}

Screen screen_init(volatile ScreenChar *characters) {
	Screen screen = {.buffer = {
						 .characters = characters,
						 .current_column = 0,
						 .current_row = 0,
					 }};

	screen_clear(&screen, get_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE));

	return screen;
};

void screen_clear(Screen *screen, unsigned char color_code) {
	screen->buffer.current_row = 0;
	screen->buffer.current_column = 0;

	for (size_t row = 0; row < VGA_BUFFER_HEIGHT; row++) {
		for (size_t column = 0; column < VGA_BUFFER_WIDTH; column++) {
			size_t index = row * VGA_BUFFER_WIDTH + column;
			screen->buffer.characters[index] =
				(ScreenChar){.ascii_character = ' ', .color_code = color_code};
		}
	}
}

void screen_write(Screen *screen, unsigned char color_code, unsigned char c) {
	size_t index = screen->buffer.current_row * VGA_BUFFER_WIDTH +
				   screen->buffer.current_column;
	screen->buffer.characters[index] = (ScreenChar){
		.ascii_character = c,
		.color_code = color_code,
	};

	if (++screen->buffer.current_column == VGA_BUFFER_WIDTH) {
		screen->buffer.current_column = 0;

		if (++screen->buffer.current_row == VGA_BUFFER_HEIGHT) {
			screen->buffer.current_row = 0;
		}
	}
}
