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

#pragma bank 0


#include "lib/colors.h"
#include "lib/palettes.h"
#include "lib/tileset.h"

#include "acorn.h"
#include "../res/drops.h"


struct Acorn acorn;

const palette_color_t P_ACORN[4] = {
    C_CLEAR, C_BLACK, C_VIOLET_2, C_ORANGE_4 };

static u8 TILE_SPR_0;


void acorn_init(void)
{
    // set_sprite_tile(SPRITE_ACORN, TILE_SPR(TILE_ACORN));

    // acorn.x = 0;
    // acorn.y = 0;
    // acorn.palette = S_PALETTE_3;
    // acorn.needs_redraw = false;
}


void acorn_init_tiles(void)
{
    // TILE_SPR_0 = tileset_init_sprite_tiles(1, drops_tiles + TILE_OFFSET(0));
}


void acorn_update(void)
{
    // acorn.props = acorn.palette;

    // switch ((acorn.x >> 2) % 4) {
    //     case 1: acorn.props |= S_FLIPY; break;
    //     case 2: acorn.props |= S_FLIPX | S_FLIPY; break;
    //     case 3: acorn.props |= S_FLIPX; break;
    // }

    // acorn.needs_redraw = true;
}


void acorn_update_xy(u8 x, u8 y)
{
    // acorn.x = x;
    // acorn.y = y;

    // acorn_update();
}


void acorn_draw(void)
{
    // if (!acorn.needs_redraw)
    //     return;

    // set_sprite_prop(SPRITE_ACORN, acorn.props);
    // move_sprite(SPRITE_ACORN, acorn.x, acorn.y);

    // acorn.needs_redraw = false;
}
