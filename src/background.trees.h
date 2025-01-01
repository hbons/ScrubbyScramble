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

#include "../res/tree_solids.h"
#include "../res/tree_left_1.h"
#include "../res/tree_left_2.h"
#include "../res/tree_left_3.h"
#include "../res/tree_right_1.h"
#include "../res/tree_right_2.h"
#include "../res/tree_right_3.h"


extern u8 TILE_BKG_0_tree_solids;
extern u8 TILE_BKG_0_tree_left_1;
extern u8 TILE_BKG_0_tree_left_2;
extern u8 TILE_BKG_0_tree_left_3;
extern u8 TILE_BKG_0_tree_right_1;
extern u8 TILE_BKG_0_tree_right_2;
extern u8 TILE_BKG_0_tree_right_3;


void background_draw_trees(void);
void background_draw_solids(void);
void background_draw_trees_left(void);
void background_draw_trees_right(void);
