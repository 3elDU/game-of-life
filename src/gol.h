#ifndef GOL_H
#define GOL_H

#include <ncurses.h>

#define ALIVE_CELL 'O'
#define DEAD_CELL ' '

// Structure for Game of Life simulation
struct GOL {
    // Width and height of a field
    unsigned width, height;

    // The field itself. Note that it is 2D
    bool *map;
};


/*
    Because the array is 1D, and the field is 2D,
    x and y coordinates needs to be converted
*/
unsigned int GOL_Convert_Pos(const struct GOL* sim, unsigned int x, unsigned int y);

/*
    Returns cell at given position.
    If position is invalid, returns 0 ( false )
*/
bool GOL_Get_Cell(const struct GOL* sim, unsigned int x, unsigned int y);
/*
    The function for initializing the GOL structure.
    It allocates memory for the map, and sets some variables.

    @return pointer to the newly created structure
*/
struct GOL* GOL_Init(unsigned width, unsigned height);

/*
    Resizes the map to new size. Useful when resizing the terminal
*/
struct GOL* GOL_Resize(struct GOL* sim, unsigned newx, unsigned newy);

/*
    Sets cell at given position with given value.
    If position is invalid, doesn't do anything
*/
void GOL_Set_Cell(struct GOL* sim, unsigned int x, unsigned int y, bool value);

/*
    Fills the field with alive or dead cells randomly (50/50)

    @args structure that will be modified
*/
void GOL_Fill_Random(struct GOL* sim);

/*
    Calculates neighboars around the cell
*/
unsigned GOL_Get_Neighbors(const struct GOL* sim, unsigned x, unsigned y);

/*
    Updates the simulation

    @args structure that will be updated
*/
void GOL_Tick(struct GOL* sim);

/*
    Renders the simulation to given ncurses window
*/
void GOL_Render(const struct GOL* sim, WINDOW* win, unsigned startx, unsigned starty);

#endif