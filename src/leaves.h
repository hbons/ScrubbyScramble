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
#include "player.h"


#ifndef LEAVES_H
#define LEAVES_H

struct Leaf {
    bool active;

    u8 x, y, z;
    u8 left, right, top, bottom;
    enum Direction direction;

    u8 sprite;
    u8 palette;
    u8 props;

    u8 tile;
    u8 tile_normal;
    u8 tile_shaded;
    u8 tile_bonus;

    bool is_shaded;
    bool is_bonus;

    u8 timer;
    u8 frame;
};

#endif


extern const palette_color_t P_LEAVES[4];

#define SPRITE_SEED_2 31
#define SPRITE_LEAF_FIRST 32

extern u8 TILE_SPR_LEAVES_0; // Hack for ending screen to draw leaves

#define TILE_LEAF_1 0
#define TILE_LEAF_2 1
#define TILE_LEAF_3 2
#define TILE_SEED_1_A 3
#define TILE_SEED_1_B 4
#define TILE_SEED_2_A 5
#define TILE_SEED_2_B 6
#define TILE_SEED_3_A 7
#define TILE_SEED_3_B 8

#define N_LEAVES 8
#define LEAF_FLOOR_TIMEOUT 24
extern struct Leaf leaves[N_LEAVES];


void leaves_init(void);
void leaves_init_tiles(void);
void leaves_update(void);
void leaves_update_bounds(struct Leaf* leaf);
void leaves_draw(void);

void leaves_reset(struct Leaf* leaf);
void leaves_spawn(void);
u8 leaf_spawn_x(u8 n);
