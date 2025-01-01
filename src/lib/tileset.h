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


#include "headers.h"


#define TILE_SIZE 8
#define TILE_BYTES 16
#define TILE_EMPTY 0x00

#define TILE_OFFSET(tile) (TILE_BYTES * tile)
#define TILE_BKG(tile) (TILE_BKG_0 + tile)
#define TILE_SPR(tile) (TILE_SPR_0 + tile)


void tileset_init(void);
u8 tileset_init_sprite_tiles(u8 count, const u8* tiles);
u8 tileset_init_bkg_tiles(u8 count, const u8* tiles);

void tileset_clear_all(void);
void tileset_clear_bkg(void);
void tileset_clear_sprite(void);
