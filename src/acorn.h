//  Copyright (C) 2024  Hylke Bons (hylke@planetpeanut.studio)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.


#include "lib/headers.h"


#define SPRITE_ACORN 30
#define TILE_ACORN 0
extern const palette_color_t P_ACORN[4];


#ifndef ACORN_H
#define ACORN_H

struct Acorn {
    u8 x;
    u8 y;
    u8 palette;
    u8 props;
    bool needs_redraw;
};

#endif


extern struct Acorn acorn;


void acorn_init(void);
void acorn_init_tiles(void);
void acorn_update(void);
void acorn_update_xy(u8 x, u8 y);
void acorn_draw(void);
