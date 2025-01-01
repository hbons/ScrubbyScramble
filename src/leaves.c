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


#include "lib/clock.h"
#include "lib/palettes.h"
#include "lib/tileset.h"
#include "lib/util.h"

#include "leaves.h"
#include "stage.h"

#include "../res/drops.h"


// No dark->light order here. needs to align with P_ACORN for shaded bonus seed
const palette_color_t P_LEAVES[4] = {
    C_BLACK, C_ORANGE_3, C_RED_1, C_RED_2 };

struct Leaf leaves[N_LEAVES];


static u8 TILE_SPR_0;
u8 TILE_SPR_LEAVES_0;


u8 spawn_index = 0;
#define N_SPAWNS 32

// 1: Leaf, 4: Bonus
const u8 stage_1_spawns[N_SPAWNS] = {
    1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
    1, 1, 0, 0, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1 };

// const u8 stage_1_spawns[N_SPAWNS] = {
//     1, 0, 0, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// const u8 stage_1_spawns[N_SPAWNS] = {
//     1, 0, 0, 1, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


void leaves_init(void)
{
    spawn_index = 0;
    struct Leaf *leaf = &leaves[0];

    u8 tile = 0; // Set different colors
    for (u8 i = 0; i != N_LEAVES; i++) {
        leaf->sprite = SPRITE_LEAF_FIRST + i;

        leaf->tile = TILE_LEAF_1 + tile;
        leaf->tile_normal = leaf->tile;
        leaf->tile_shaded = 1;
        if (tile == 0) leaf->tile_shaded = 2;
        if (tile == 2) leaf->tile_shaded = 1;
        tile = (tile + 1) % 3;

        if (rand() % 2)
            leaf->direction = DIRECTION_RIGHT;

        leaves_reset(leaf);
        leaf++;
    }
}


void leaves_init_tiles(void)
{
    TILE_SPR_0 = tileset_init_sprite_tiles(9, drops_tiles + TILE_OFFSET(1));
    TILE_SPR_LEAVES_0 = TILE_SPR_0;
}


void leaves_reset(struct Leaf* leaf)
{
    leaf->active = false;
    hide_sprite(leaf->sprite);

    if (leaf->is_bonus) {
        hide_sprite(SPRITE_SEED_2);
        STAGE_BONUS_ACTIVE = false;
    }

    leaf->x = leaf_spawn_x(leaf->sprite);
    leaf->y = 0;

    leaf->tile = leaf->tile_normal;
    leaf->palette = S_PALETTE_4;
    leaf->props = leaf->palette;

    leaf->is_bonus = false;
    leaf->timer = LEAF_FLOOR_TIMEOUT;
    leaf->frame = 0;

    leaves_update_bounds(leaf);
}


u8 leaf_spawn_x(u8 n)
{
    const u8 tree_width = 80;
    u8 x = util_rand_max(tree_width);

    if (n % 2) // Spawn from either side of screen
        return x + 1;
    else
        return DEVICE_SCREEN_PX_WIDTH - (x - 8);
}


void leaves_update_bounds(struct Leaf* leaf)
{
    leaf->left   = leaf->x;
    leaf->right  = leaf->x + 8;
    leaf->top    = leaf->y;
    leaf->bottom = leaf->y + 8;
}


const u8 seed_tiles[8] = { 0, 2, 4, 2, 0, 2, 4, 2 };

void seed_animate(struct Leaf *seed)
{
    seed->palette = seed->is_shaded ? S_PALETTE_4 : S_PALETTE_3; // Acorn
    seed->props   = seed->palette;

    seed->tile       = TILE_SEED_1_A;
    seed->tile_bonus = TILE_SEED_1_B;
    seed->tile       += seed_tiles[seed->frame];
    seed->tile_bonus += seed_tiles[seed->frame];

    if (seed->frame >= 3 && seed->frame <= 5) {
        seed->props |= S_FLIPX;

        u8 t = seed->tile;
        seed->tile = seed->tile_bonus;
        seed->tile_bonus = t;
    }

    seed->frame += 1;

    if (seed->frame == 8)
        seed->frame = 0;
}


void leaves_spawn(void)
{
    u8 spawn = stage_1_spawns[spawn_index];
    spawn_index++;

    if (spawn_index == N_SPAWNS)
        spawn_index = 0;

    if (spawn == 0)
        return;

    struct Leaf *leaf = &leaves[0];

    for (u8 i = 0; i != N_LEAVES; i++) {
        if (leaf->active)
            goto next;

        if (spawn == 4) {
            leaf->is_bonus = true;
            STAGE_BONUS_ACTIVE = true;
        }

        leaf->active = true;
        break;

        next:
        leaf++;
    }
}


void leaves_update(void)
{
    if (CLOCK_TICK_64 && !STAGE_BONUS_ACTIVE)
        leaves_spawn();

    struct Leaf *leaf = &leaves[0];

    for (u8 i = 0; i != N_LEAVES; i++) {
        if (!leaf->active)
            goto next;

        u8 tile = leaf->tile_normal;
        u8 props = leaf->palette;
        u8 x = leaf->x;
        u8 y = leaf->y;

        // Dark shade leaf when in front of moon
        leaf->is_shaded = ((x >= 144 && x <= 184) && (y >= 104 && y <= 136));

        // Reset after hitting the ground
        if (y >= STAGE_GROUND_Y + 12) {
            if (leaf->timer == 0)
                leaves_reset(leaf);
            else
                leaf->timer--;

            goto next;
        }

        if (!CLOCK_EVEN)
            goto next;

        u8 speed_x = 1;
        u8 speed_y = 1;

        if (CLOCK_TICK_4) {
            if (leaf->is_bonus) {
                speed_x = 2;
                speed_y = 0;

                if (y == 48)
                    leaf->direction = DIRECTION_RIGHT;

                if (y == 144) {
                    bool coin_flip = (rand() % 2 == 0);
                    if (coin_flip) leaf->direction = DIRECTION_LEFT;
                }
            }

            if (leaf->direction)
                x += speed_x;
            else
                x -= speed_x;
        }

        y += speed_y;
        if (i % 2) props |= S_FLIPX;

        if (leaf->is_bonus) {
            if (CLOCK_TICK_8)
                seed_animate(leaf);

            if (y == 112) // Allow for breathing time after bonus
                STAGE_BONUS_ACTIVE = false;

        } else {
            if (leaf->is_shaded) tile = leaf->tile_shaded;

            leaf->tile = tile;
            leaf->props = props | leaf->palette;
        }

        leaf->x = x;
        leaf->y = y;

        next:
        leaves_update_bounds(leaf);
        leaf++;
    }
}


void leaves_draw(void)
{
    struct Leaf *leaf = &leaves[0];

    for (u8 i = 0; i != N_LEAVES; i++) {
        // Draw behind trees
        if (leaf->y <= STAGE_CANOPY_Y) leaf->props |= S_PRIORITY;

        if (!leaf->active)
            goto next;

        if (leaf->is_bonus) {
            set_sprite_tile(SPRITE_SEED_2, TILE_SPR(leaf->tile_bonus));
            set_sprite_prop(SPRITE_SEED_2, leaf->props);

            // Center the bonus hitbox
            move_sprite(leaf->sprite,  leaf->x - 4,     leaf->y);
            move_sprite(SPRITE_SEED_2, leaf->x - 4 + 8, leaf->y);
        } else {
            move_sprite(leaf->sprite, leaf->x, leaf->y);
        }

        set_sprite_tile(leaf->sprite, TILE_SPR(leaf->tile));
        set_sprite_prop(leaf->sprite, leaf->props);

        next:
        leaf++;
    }
}
