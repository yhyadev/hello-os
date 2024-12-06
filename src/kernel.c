#include <stdbool.h>
#include <stddef.h>

enum VGA_COLOR {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

#define VGA_BUFFER_ADDRESS 0xb8000
#define VGA_BUFFER_WIDTH 25
#define VGA_BUFFER_HEIGHT 80

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

size_t strlen(const char *string) {
    size_t len = 0;

    while (string[len]) len++;

    return len;
}

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


void screen_write_string(Screen *screen, const char *string) {
    unsigned char color_code = get_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE);

    for (size_t i = 0; i < strlen(string); i++) {
        screen_write(screen, color_code, string[i]);
    }
}

void kmain(void) {
    Screen screen = screen_init((volatile ScreenChar *)VGA_BUFFER_ADDRESS);

    screen_write_string(&screen, "Hello, World!");

    while (true) {}
}
