#ifndef BORDERS_H
#define BORDERS_H

#include <ncurses.h>

struct BorderType {
    chtype up;
    chtype down;
    chtype left;
    chtype right;

    chtype upperLeft;
    chtype upperRight;

    chtype bottomLeft;
    chtype bottomRight;
};

struct BorderPosition {
    unsigned startx, starty, endx, endy;
};

void Custom_Border(WINDOW* win, const struct BorderType type, const struct BorderPosition pos);

#endif