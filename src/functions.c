#include "functions.h"

void Fill_Window(WINDOW* win, char ch) {
    unsigned startx = 0, starty = 0, maxx = getmaxx(win), maxy = getmaxy(win);

    for (int y = starty; y <= maxy; y++) {
        mvwhline(win, y, startx, ch, maxx);
    }
}