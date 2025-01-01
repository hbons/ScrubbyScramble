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
#include "lib/colors.h"
#include "lib/game.h"
#include "lib/joypad.h"
#include "lib/palettes.h"
#include "lib/tileset.h"

#include "acorn.h"
#include "player.h"
#include "stage.h"

#include "../res/player.h"


const palette_color_t P_HEDGEHOG_1[4] = {
    C_CLEAR, C_TEAL_1, C_TEAL_2, C_ORANGE_4 };

const palette_color_t P_HEDGEHOG_2[4] = {
    C_CLEAR, C_PURPLE_1, C_PURPLE_2, C_ORANGE_4 };


struct Player player1;
struct Player player2;

const u8 WINK_TIMEOUT = 45;

const u8 player_tileset[] = {
    TILE_HEDGEHOG_A,
    TILE_HEDGEHOG_B,
    TILE_HEDGEHOG_C,
    TILE_HEDGEHOG_D,
    TILE_HEDGEHOG_E,
};

static u8 TILE_SPR_0;


void player_init(void)
{
    player_init_p1();
    player_init_p2();

    for (u8 i = 0; i != 5; i++) {
        u8 tile = TILE_SPR(player_tileset[i]);
        set_sprite_tile(player1.first_sprite + i, tile);
        set_sprite_tile(player2.first_sprite + i, tile);
    }

    set_sprite_tile(SPRITE_PLAYER_1_SCORE_1, TILE_SPR(TILE_SCORE_10_LITE));
    set_sprite_tile(SPRITE_PLAYER_1_SCORE_2, TILE_SPR(TILE_SCORE_0_LITE));
    set_sprite_tile(SPRITE_PLAYER_2_SCORE_1, TILE_SPR(TILE_SCORE_10_LITE));
    set_sprite_tile(SPRITE_PLAYER_2_SCORE_2, TILE_SPR(TILE_SCORE_0_LITE));
}


void player_init_tiles(void)
{
    TILE_SPR_0 = tileset_init_sprite_tiles(player_TILE_COUNT, player_tiles);
}


void player_init_common(void)
{
    player1.width  = 24;
    player1.height = 16;

    player1.score = 0;
    player1.y = STAGE_GROUND_Y - 1;
    player1.wink = false;
    player1.wink_timer = WINK_TIMEOUT;

    player1.needs_redraw = true;
    player1.needs_move = true;

    player1.top    = player1.y;
    player1.left   = player1.x;
    player1.right  = player1.left + player1.width;
    player1.bottom = player1.top  + player1.height;
}

void player_init_p1(void)
{
    player_init_common();

    player1.pad = J_PAD_1;
    player1.button_left = J_LEFT;
    player1.button_right = J_RIGHT;
    player1.opponent = &player2;

    player1.x = 88;
    player1.direction = DIRECTION_RIGHT;

    player1.palette = S_PALETTE_1;
    player1.first_sprite = SPRITE_PLAYER_1_A;
    player1.score_sprite_1 = SPRITE_PLAYER_1_SCORE_1;
    player1.score_sprite_2 = SPRITE_PLAYER_1_SCORE_2;
}


void player_init_p2(void)
{
    player_init_common();
    player2 = player1;

    player2.pad = J_PAD_1; // Allow playing on a single joypad
    player2.button_left = J_B;
    player2.button_right = J_A;
    player2.opponent = &player1;

    player2.x = 144;
    player2.direction = DIRECTION_LEFT;

    player2.left   = player2.x;
    player2.top    = player2.y;
    player2.right  = player2.left + player2.width;
    player2.bottom = player2.top  + player2.height;

    player2.palette = S_PALETTE_2;
    player2.first_sprite = SPRITE_PLAYER_2_A;
    player2.score_sprite_1 = SPRITE_PLAYER_2_SCORE_1;
    player2.score_sprite_2 = SPRITE_PLAYER_2_SCORE_2;
}


void player_update(void)
{
    // Use the 2nd joypad if input is detected on it
    if (joypad_changed(J_PAD_2)) {
        player2.pad = J_PAD_2;
        player2.button_left = J_LEFT;
        player2.button_right = J_RIGHT;
    }

    player_update_joypad(&player1);
    player_update_joypad(&player2);

    player_wink(&player1);
    player_wink(&player2);
}


void player_wink(struct Player* player)
{
    if (player->wink_timer == 0) {
        player->wink = false;
        player->wink_timer = WINK_TIMEOUT;
        player->needs_redraw = true;
    }

    if (player->wink)
        player->wink_timer -= 1;
}


void player_update_joypad(struct Player *player)
{
    if (joypad_button_down(player->pad,
                           player->button_left)) {

        if (player->direction == DIRECTION_RIGHT)
            player->needs_redraw = true;

        player->direction = DIRECTION_LEFT;
        u8 new_left = player->left - 1;

        if (player->opponent->right == 255 && new_left == 0)
            return; // Screen edge check

        if (player->left > player->opponent->right) {
            if (new_left == player->opponent->right)
                return;
        }

        player->x = new_left;
        player->left = new_left;
        player->right = new_left + player->width;

        player->needs_move = true;
    }

    if (joypad_button_down(player->pad,
                           player->button_right)) {

        if (player->direction == DIRECTION_LEFT)
            player->needs_redraw = true;

        player->direction = DIRECTION_RIGHT;
        u8 new_right = player->right + 1;

        if (player->opponent->left == 0 && new_right == 255)
            return; // Screen edge check

        if (player->right <= player->opponent->left) {
            if (new_right == player->opponent->left)
                return;
        }

        player->x = new_right - player->width;
        player->left = player->x;
        player->right = new_right;

        player->needs_move = true;
    }
}


void player_draw(void)
{
    if (player1.needs_redraw)
        player_direction(&player1);
    if (player1.needs_move)
        player_move(&player1);

    if (player2.needs_redraw)
        player_direction(&player2);
    if (player2.needs_move)
        player_move(&player2);
}


void player_direction(struct Player *player)
{
    u8 props = player->palette;
    u8 props_head = S_PALETTE_3;

    if (player->direction == DIRECTION_LEFT) {
        props |= S_FLIPX;
        props_head |= S_FLIPX;
    }

    for (u8 i = 0; i != 5; i++) {
        if (i == 4)
            props = props_head;

        set_sprite_prop(player->first_sprite + i, props);
    }

    u8 tile = player->wink ? TILE_HEDGEHOG_WINK : TILE_HEDGEHOG_E;
    set_sprite_tile(player->first_sprite + 4, TILE_SPR(tile));

    player_score(player);
}


void player_score(struct Player *player)
{
    hide_sprite(player->score_sprite_1);
    hide_sprite(player->score_sprite_2);

    if (!player->wink || GAME_STATE != G_MAIN)
        return; // Don't draw the score on wins or game end

    u8 tile1 = TILE_SCORE_10_LITE;
    u8 tile2 = TILE_SCORE_0_LITE;
    u8 palette = player->palette;

    if (player->last_score == STAGE_SCORE_PTS_BONUS) {
        tile1 = TILE_SCORE_40_LITE;
        palette = S_PALETTE_3; // Acorn
    }

    if (CLOCK_INTERVAL_4) {
        tile1++; // Flash to dark tiles
        tile2++;
    }

    set_sprite_tile(player->score_sprite_1, TILE_SPR(tile1));
    set_sprite_tile(player->score_sprite_2, TILE_SPR(tile2));
    set_sprite_prop(player->score_sprite_1, palette);
    set_sprite_prop(player->score_sprite_2, palette);

    move_sprite(player->score_sprite_1, player->x + 4,     player->y - 10);
    move_sprite(player->score_sprite_2, player->x + 4 + 8, player->y - 10);
}


const u8 x_offsets_left[]  = { 16,  8, 16,  8,  0 };
const u8 x_offsets_right[] = {  0,  8,  0,  8, 16 };
const u8 y_offsets[]       = {  0,  0,  8,  8,  8 };

void player_move(struct Player *player)
{
    const u8 *x_offsets = x_offsets_right;

    if (player->direction == DIRECTION_LEFT)
        x_offsets = x_offsets_left;

    for (u8 i = 0; i != 5; i++, x_offsets++) {
        move_sprite(player->first_sprite + i,
            player->x + *x_offsets,
            player->y + y_offsets[i]);
    }
}
