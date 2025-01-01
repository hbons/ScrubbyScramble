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
#include "../res/floor.h"


extern u8 TILE_BKG_0_floor;
extern const u8 fence_map[4][4];
extern const u8 pavement_map[20];

void background_draw_floor(void);
void background_draw_grass(u8 col1, u8 row1, u8 col2, u8 row2);
