#include "borders.h"

void Custom_Border(WINDOW* win, const struct BorderType type, const struct BorderPosition pos) {
    // +    +
    //
    // +    +
    mvaddch(pos.starty, pos.startx, type.upperLeft);
    mvaddch(pos.endy,   pos.startx, type.bottomLeft);
    mvaddch(pos.starty, pos.endx,   type.upperRight);
    mvaddch(pos.endy,   pos.endx,   type.bottomRight);

    //  ----
    //
    //  ----
    mvwhline(win, pos.starty, pos.startx+1, type.up,   pos.endx-pos.startx-1);
    mvwhline(win, pos.endy,   pos.startx+1, type.down, pos.endx-pos.startx-1);

    //
    // |    |
    //
    mvwvline(win, pos.starty+1, pos.startx, type.left,  pos.endy-pos.starty-1);
    mvwvline(win, pos.starty+1, pos.endx,   type.right, pos.endy-pos.starty-1);
}
