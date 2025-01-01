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


#define SPRITE_PLAYER_1_A 16
#define SPRITE_PLAYER_1_B 17
#define SPRITE_PLAYER_1_C 18
#define SPRITE_PLAYER_1_D 19
#define SPRITE_PLAYER_1_E 20
#define SPRITE_PLAYER_1_SCORE_1 21
#define SPRITE_PLAYER_1_SCORE_2 22

#define SPRITE_PLAYER_2_A 23
#define SPRITE_PLAYER_2_B 24
#define SPRITE_PLAYER_2_C 25
#define SPRITE_PLAYER_2_D 26
#define SPRITE_PLAYER_2_E 27
#define SPRITE_PLAYER_2_SCORE_1 28
#define SPRITE_PLAYER_2_SCORE_2 29

#define TILE_HEDGEHOG_A 0
#define TILE_HEDGEHOG_B 2
#define TILE_HEDGEHOG_C 1
#define TILE_HEDGEHOG_D 3
#define TILE_HEDGEHOG_E 5
#define TILE_HEDGEHOG_WINK 4

#define TILE_SCORE_10_LITE 6
#define TILE_SCORE_10_DARK 7
#define TILE_SCORE_40_LITE 8
#define TILE_SCORE_40_DARK 9
#define TILE_SCORE_0_LITE 10
#define TILE_SCORE_0_DARK 11

extern const palette_color_t P_HEDGEHOG_1[4];
extern const palette_color_t P_HEDGEHOG_2[4];


#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    u8 pad;
    u8 button_left;
    u8 button_right;
    struct Player* opponent;

    u8 x, y;
    u8 width, height;
    u8 left, right, top, bottom;
    enum Direction direction;

    u8 score;
    u8 last_score;

    u8 palette;
    u8 first_sprite;
    u8 score_sprite_1;
    u8 score_sprite_2;
    bool wink;
    u8 wink_timer;

    bool needs_redraw;
    bool needs_move;
};

enum Direction
{
    DIRECTION_LEFT  = 0,
    DIRECTION_RIGHT = 1
};

#endif


extern struct Player player1;
extern struct Player player2;

void player_init(void);
void player_init_tiles(void);
void player_init_common(void);
void player_init_p1(void);
void player_init_p2(void);
void player_update(void);
void player_update_joypad(struct Player *player);
void player_draw(void);

void player_wink(struct Player* player);
void player_direction(struct Player *player);
void player_move(struct Player *player);
void player_score(struct Player *player);
