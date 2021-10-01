#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>

#include <ncurses.h>

#include "gol.h"
#include "borders.h"

int main(int argc, char *argv[]) {
    // Setting locale for Unicode support
    setlocale(LC_ALL, "");

    // Setting random seed
    srand( (unsigned int) time(0) );

    // Initalizing ncurses, and refreshing the screen ( fixes some strange bugs )
    initscr();
    refresh();

    // If terminal doesn't support colors, exiting
    if (has_colors() == FALSE) {
        printw("Your terminal doesn't support colors!\nPress any key to exit\n");

        getch();
        endwin();
        return 1;
    }

    // Enabling colors
    start_color();

    // Do not write characters when they're pressed
    noecho();

    // Monitor raw input ( no Ctrl+C, etc. )
    cbreak();

    // Enable function (F1, F2, etc) and arrow keys
    keypad(stdscr, true);

    // Disabling cursor ( in terminal, not in the whole system)
    curs_set(0);

    // Disabling delay for getch()
    nodelay(stdscr, true);

    // Disabling delay when pressing Escape
    set_escdelay(0);

    // Structure with characters used to draw border
    struct BorderType mainBorder = {.up=ACS_HLINE, .down=ACS_HLINE, .left=ACS_VLINE, .right=ACS_VLINE,
                                    .upperLeft=ACS_ULCORNER, .upperRight=ACS_URCORNER,
                                    .bottomLeft=ACS_LLCORNER, .bottomRight=ACS_LRCORNER};


    // Drawing border around the screen
    Custom_Border(stdscr, mainBorder, (struct BorderPosition){0, 0, getmaxx(stdscr)-1, getmaxy(stdscr)-2});

    // Creating separate window, where simulation will be drawn
    WINDOW *gol_window = newwin(getmaxy(stdscr)-3, getmaxx(stdscr)-3, 1, 1);

    // Refreshing main window, and simulation window
    refresh();
    wrefresh(gol_window);

    // Creating Game of Life simulation
    struct GOL* sim = GOL_Init(getmaxx(gol_window), getmaxy(gol_window));
    GOL_Fill_Random(sim);

    // Running indicates is main loop running ( e.g. when we want to exit, we just set it to false )
    // Paused speaks for itself
    bool running = true, paused = false;

    while (running) {

        // Monitoring key press events
        int ch = getch();
        switch (ch) {
            case ' ': { // Space key, pausing/unpausing when it is pressed
                paused = !paused;

                break;
            }


            case 27: { // Exiting on Escape, q or Q keys
                running = false;

                break;
            }
            case 'q': {
                running = false;

                break;
            }
            case 'Q': {
                running = false;

                break;
            }

            case KEY_RIGHT: {
                GOL_Tick(sim);

                break;
            }


            case 'r' : { // Reload the sumulation
                GOL_Fill_Random(sim);

                break;
            }

            case KEY_RESIZE: { // When resizing the window
                sim = GOL_Resize(sim, getmaxx(stdscr)-2, getmaxy(stdscr)-3);
                wresize(gol_window, getmaxx(stdscr)-2, getmaxy(stdscr)-3);

                wclear(gol_window);
                wclear(stdscr);

                // Drawing border around the screen
                Custom_Border(stdscr, mainBorder, (struct BorderPosition){0, 0, getmaxx(stdscr)-1, getmaxy(stdscr)-2});

                break;
            }

            default : {
                break;
            }
        }


        // Rendering
        GOL_Render(sim, gol_window, getbegy(gol_window), getbegx(gol_window));

        // Menu
        mvprintw(getmaxy(stdscr)-1, 0, "[F1] Settings  [Space] Pause/Unpause  [Right Arrow] Step Forward [Q or Esc] Quit");

        // Refreshing the screen
        wrefresh(gol_window);
        refresh();

        // Updating game of life simulation
        if (!paused) GOL_Tick(sim);

        // Adding some delay ( 1/100 th of a second, so we run at 100 fps )
        usleep(10000);
    }

    // Deallocating resources owned by ncurses, and exiting
    endwin();
    return 0;
}
