#include "stdlib.h"

/* Hardware text mode color constants. */
enum vga_colour {
  VGA_COLOUR_BLACK,
  VGA_COLOUR_BLUE,
  VGA_COLOUR_GREEN,
  VGA_COLOUR_CYAN,
  VGA_COLOUR_RED,
  VGA_COLOUR_MAGENTA,
  VGA_COLOUR_BROWN,
  VGA_COLOUR_LIGHT_GREY,
  VGA_COLOUR_DARK_GREY,
  VGA_COLOUR_LIGHT_BLUE,
  VGA_COLOUR_LIGHT_GREEN,
  VGA_COLOUR_LIGHT_CYAN,
  VGA_COLOUR_LIGHT_RED,
  VGA_COLOUR_LIGHT_MAGENTA,
  VGA_COLOUR_LIGHT_BROWN,
  VGA_COLOUR_WHITE,
};

static
const size_t VGA_WIDTH = 80;
static
const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_colour;
uint16_t * terminal_buffer;

extern _timestampedx();
extern _timestampeax();

static inline uint8_t vga_entry_color(enum vga_colour foreground, enum vga_colour background) {
  return foreground | (background << 4);
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_initialize() {
  terminal_row = 0;
  terminal_column = 0;
  terminal_colour = vga_entry_color(VGA_COLOUR_WHITE, VGA_COLOUR_BLUE);
  terminal_buffer = (uint16_t * ) 0xB8000;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_colour);
    }
  }
}

void terminal_putcharat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {

  if (terminal_column == VGA_WIDTH || c == '\n') {
    terminal_column = 0;
    if (terminal_row == VGA_HEIGHT - 1) {
      terminal_scroll_up();
    } else {
      terminal_row++;
    }
  }
  if (c == '\n') return;
  terminal_putcharat(c, terminal_colour, terminal_column++, terminal_row);
}

void terminal_write(const char * data, size_t size) {

  for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_writestring(const char * data) {

  terminal_write(data, strlen(data));
}
// <newstuff>

void terminal_scroll_up() {
  int i;
  for (i = 0; i < (VGA_WIDTH * VGA_HEIGHT - 80); i++)
    terminal_buffer[i] = terminal_buffer[i + 80];
  for (i = 0; i < VGA_WIDTH; i++)
    terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = vga_entry(' ', terminal_colour);

}

void terminal_writestring_colour(const char * data, enum vga_colour fg, enum vga_colour bg) {
  uint8_t oldcolour = terminal_colour;
  terminal_colour = vga_entry_color(fg, bg);
  terminal_writestring(data);
  terminal_colour = oldcolour;
}

void terminal_writeint(unsigned long n) {
  if (n / 10)
    terminal_writeint(n / 10);
  terminal_putchar((n % 10) + '0');

}

//</newstuff>

void kernel_main(void) {
  int a;
  terminal_initialize();
  srand(_timestampeax);
  terminal_writestring("                           ");
  terminal_writestring_colour(",---------------------------,\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("|  /---------------------\\  |\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("| |", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring_colour("                       ", VGA_COLOUR_WHITE, VGA_COLOUR_WHITE);
  terminal_writestring_colour("| |\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("| |", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring_colour("       Welcome to      ", VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);
  terminal_writestring_colour("| |\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("| |", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring_colour("      Basilica OS      ", VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);
  terminal_writestring_colour("| |\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("| |", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring_colour("        V 1.0          ", VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);
  terminal_writestring_colour("| |\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("| |", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring_colour("                       ", VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);
  terminal_writestring_colour("| |\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("| |", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring_colour("  C:\\>                 ", VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);
  terminal_writestring_colour("| |\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("|  \\_____________________/  |\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                           ");
  terminal_writestring_colour("|___________________________|\n", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring("                         ");
  terminal_writestring_colour(",---", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring_colour("\\_____     ", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring_colour("[]", VGA_COLOUR_RED, VGA_COLOUR_BLACK);
  terminal_writestring_colour("     _______/", VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
  terminal_writestring_colour("------,\n", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring("                       ");
  terminal_writestring_colour("/         /______________\\           /|\n", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring("                     ");
  terminal_writestring_colour("/___________________________________ /  |\n", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring("                     ");
  terminal_writestring_colour("|                                   |   |\n", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring("                     ");
  terminal_writestring_colour("|  _ _ _                 [-------]  |   |\n", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring("                     ");
  terminal_writestring_colour("|  ", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring_colour("o ", VGA_COLOUR_BLUE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring_colour("o ", VGA_COLOUR_GREEN, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring_colour("o                 ", VGA_COLOUR_RED, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring_colour("[-------]  |  /\n", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);
  terminal_writestring("                     ");
  terminal_writestring_colour("|__________________________________ |/\n", VGA_COLOUR_WHITE, VGA_COLOUR_LIGHT_GREY);

  for (;;) {
    terminal_row = VGA_HEIGHT - 3;
    terminal_column = 4;
    terminal_writestring_colour("System Time-Stamp:", VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);
    terminal_putchar(' ');
    terminal_writeint(_timestampedx());
    terminal_writeint(_timestampeax());
    terminal_writestring("                \n    ");
    terminal_writestring_colour("rand():", VGA_COLOUR_BLACK, VGA_COLOUR_WHITE);
    terminal_putchar(' ');
    terminal_writeint(rand());
    terminal_writestring("              ");
    terminal_putcharat('_', vga_entry_color(VGA_COLOUR_BLACK, VGA_COLOUR_WHITE), 37, 7);
    delay(500);
    terminal_putcharat(' ', vga_entry_color(VGA_COLOUR_BLACK, VGA_COLOUR_WHITE), 37, 7);
    delay(500);

  }

}
