#include "menu.h"
#include "functions.h"

#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include "borders.h"

unsigned Display_Menu(char** choices, unsigned choices_size) {
    // count maximum length
    unsigned maxLen = 0;
    for (int i = 0; i < choices_size; i++) {
        if (strlen(choices[i]) > maxLen) maxLen = strlen(choices[i]);
    }

    const unsigned int centerx = getmaxx(stdscr) / 2, centery = getmaxy(stdscr) / 2;
    const struct BorderType type = {'-','-','|','|','+','+','+','+'};
    WINDOW* menu_win = newwin(10, 10,  centery-5, centerx-5);

    for (;;) {
        Fill_Window(menu_win, '=');
        Custom_Border(menu_win, type, (const struct BorderPosition){getbegx(menu_win), getbegy(menu_win), getmaxx(menu_win), getmaxy(menu_win)});
        
        wrefresh(menu_win);
        refresh();

        int symb = getch();
        if (symb == 'q' || symb == 'Q') break;

        usleep(40000);
    }

    return 0u; 
}