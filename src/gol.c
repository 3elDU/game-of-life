#include "gol.h"

#include <stdlib.h>
#include <string.h>

/*
    Because the array is 1D, and the field is 2D,
    x and y coordinates needs to be converted
*/
unsigned int GOL_Convert_Pos(const struct GOL* sim, unsigned int x, unsigned int y) {
    return y * sim->width + x;
}

/*
    Returns cell at given position.
    If position is invalid, returns 0 ( false )
*/
bool GOL_Get_Cell(const struct GOL* sim, unsigned int x, unsigned int y) {
    if (x >= 0 && x < sim->width && y >= 0 && y < sim->height) {
        return sim->map[GOL_Convert_Pos(sim, x, y)];
    }
    return false;
}

/*
    The function for initializing the GOL structure.
    It allocates memory for the map, and sets some variables.

    @return pointer to the newly created structure
*/
struct GOL* GOL_Init(unsigned width, unsigned height) {
    struct GOL *gol = malloc(sizeof(struct GOL));

    gol->width = width, gol->height = height;

    gol->map = malloc(width * height * sizeof(bool));
    memset(gol->map, 0, width * height * sizeof(bool));

    return gol;
}

/*
    Resizes the map to new size. Useful when resizing the terminal
*/
struct GOL* GOL_Resize(struct GOL* sim, unsigned newx, unsigned newy) {
    struct GOL* newStruct = GOL_Init(newx, newy);

    for (int i = 0; i < newx; i++) {

        for (int j = 0; j < newy; j++) {

            GOL_Set_Cell(newStruct, i, j, GOL_Get_Cell(sim, i, j));
        }
    }

    free(sim);
    return newStruct;
}

/*
    Sets cell at given position with given value.
    If position is invalid, doesn't do anything
*/
void GOL_Set_Cell(struct GOL* sim, unsigned int x, unsigned int y, bool value) {
    if (x >= 0 && x < sim->width && y >= 0 && y < sim->height) {
        sim->map[GOL_Convert_Pos(sim, x, y)] = value;
    }
}

/*
    Fills the field with alive or dead cells randomly (50/50)

    @args structure that will be modified
*/
void GOL_Fill_Random(struct GOL* sim) {
    for (int i = 0; i < sim->width; i++) {
        for (int j = 0; j < sim->height; j++) {

            GOL_Set_Cell(sim, i, j, (bool)(-1+rand()%2) );
        }
    }
}

/*
    Calculates neighboars around the cell
*/
unsigned GOL_Get_Neighbors(const struct GOL* sim, unsigned x, unsigned y) {
    unsigned neighbors = 0;

    for (int i = x-1; i <= x+1; i++) {

        for (int j = y-1; j <= y+1; j++) {

            if (i == x && j == y) continue;
            else {

                if (i > 0 && i < sim->width && y > 0 && y < sim->height)
                    neighbors += (GOL_Get_Cell(sim, i, j) ? 1 : 0);
            }
        }
    }

    return neighbors;
}

/*
    Updates the simulation

    @args structure that will be updated
*/
void GOL_Tick(struct GOL* sim) {
    bool* newMap = malloc(sim->width * sim->height * sizeof(bool));
    memset(newMap, 0, sim->width * sim->height * sizeof(bool));

    for (unsigned i = 0; i < sim->width; i++) {

        for (unsigned j = 0; j < sim->height; j++) {

            unsigned neighbors = GOL_Get_Neighbors(sim, i, j);

            if (sim->map[GOL_Convert_Pos(sim, i, j)] == TRUE) {

                if (neighbors == 2 || neighbors == 3) {
                    newMap[GOL_Convert_Pos(sim, i, j)] = TRUE;
                }
                else {
                    newMap[GOL_Convert_Pos(sim, i, j)] = FALSE;
                }
            }
            else if (sim->map[GOL_Convert_Pos(sim, i, j)] == FALSE) {

                if (neighbors == 3) {
                    newMap[GOL_Convert_Pos(sim, i, j)] = TRUE;
                }
                else {
                    newMap[GOL_Convert_Pos(sim, i, j)] = FALSE;
                }
            }
        }
    }

    free(sim->map);
    sim->map = newMap;
}

/*
    Renders the simulation to given ncurses window
*/
void GOL_Render(const struct GOL* sim, WINDOW* win, unsigned startx, unsigned starty) {
    for (int j = 0; j < sim->height; j++) {
        for (int i = 0; i < sim->width; i++) {

            mvaddch(startx+j, starty+i, (sim->map[GOL_Convert_Pos(sim, i, j)] ? ALIVE_CELL : DEAD_CELL));
        }
    }
}

