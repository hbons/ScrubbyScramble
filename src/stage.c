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
#include "lib/game.h"
#include "lib/joypad.h"
#include "lib/palettes.h"
#include "lib/tileset.h"
#include "lib/util.h"

#include "acorn.h"
#include "background.h"
#include "hud.h"
#include "leaves.h"
#include "player.h"
#include "stage.h"


const palette_color_t P_BKG_LIGHTS[4] = {
    C_COMMON, C_ORANGE_3, C_TEAL_4, C_WHITE };

const palette_color_t P_BKG_DARKS[4] = {
    C_COMMON, C_CYAN_1, C_CYAN_2, C_GREEN_3 };

const palette_color_t P_BKG_HUD[4] = {
    C_COMMON, C_CYAN_1, C_PURPLE_2, C_TEAL_2 };

const palette_color_t P_BKG_LEAVES[4] = {
    C_COMMON, C_RED_1, C_RED_2, C_ORANGE_3 };


const u8 STAGE_CANOPY_Y = 48;
const u8 STAGE_GROUND_Y = 176;
bool STAGE_BONUS_ACTIVE;

static u8 player1_wins;
static u8 player2_wins;

#define WIN_TIMEOUT 180
static u8 win_timer;
static bool needs_redraw;


void stage_init(void)
{
    player_init();
    leaves_init();
    // acorn_init();
    hud_init();

    win_timer = WIN_TIMEOUT;
    needs_redraw = true;

    player1_wins = 0;
    player2_wins = 0;
}


void stage_init_tiles(void)
{
    background_init_tiles();
    player_init_tiles();
    //acorn_init_tiles();
    leaves_init_tiles();
    hud_init_tiles();
}


void stage_update(void)
{
    if (GAME_STATE == G_MAIN ||
        GAME_STATE == G_ROUND_END) {
        hud_update();
    }

    if (GAME_STATE == G_ROUND_END) {
        if (win_timer == 0) {
            win_timer = WIN_TIMEOUT;
            needs_redraw = true;
            STAGE_BONUS_ACTIVE = false;

            game_state(G_ROUND_START);
            leaves_init();
            hud_init();
            player_init();

        } else {
            win_timer--;
        }
    }

    if (GAME_STATE != G_MAIN)
        return;

    leaves_update();
    player_update();
    // acorn_update();

    if (HUD_SCORE_1 >= HUD_SCORE_WIN) {
        player1_wins += 1;
        player1.wink = true;
        game_state(G_ROUND_END);
    }

    if (HUD_SCORE_2 >= HUD_SCORE_WIN) {
        player2_wins += 1;
        player2.wink = true;
        game_state(G_ROUND_END);
    }

    stage_check_collisions(&player1);
    stage_check_collisions(&player2);
}


void stage_check_collisions(struct Player* player)
{
    struct Leaf *leaf = &leaves[0];

    for (u8 i = 0; i != N_LEAVES; i++) {
        if (!leaf->active)
            goto next;

        if (leaf->left  > leaf->right ||
            leaf->right < leaf->left) {
            goto next; // Skip leaves on the screen edges to prevent problems
        }

        if (leaf->bottom - 4 < player->top)
            goto next;

        if (leaf->left  >= player->left &&
            leaf->right <= player->right) {

            if (leaf->is_bonus) {
                player->last_score = STAGE_SCORE_PTS_BONUS;
                STAGE_BONUS_ACTIVE = false;
            } else
                player->last_score = STAGE_SCORE_PTS;

            player->score += player->last_score;

            player->wink = true;
            leaves_reset(leaf);

            hud_update_score(player1.score, player2.score);
        }

        next:
        leaf++;
    }
}


void stage_draw(void)
{
    player_draw();
    // acorn_draw();
    hud_draw();

    if (GAME_STATE != G_ROUND_END)
        leaves_draw(); // Freeze leaves on win

    if (!needs_redraw)
        return;

    background_draw();

    palettes_init_sprite(P_HEDGEHOG_1, P_HEDGEHOG_2, P_ACORN, P_LEAVES);
    palettes_init_bkg(P_BKG_LEAVES, P_BKG_LIGHTS, P_BKG_DARKS, P_BKG_HUD);

    needs_redraw = false;
}


// 0: No winner yet
// 1: Player 1 won
// 2: Player 2 won
u8 stage_get_winner(void)
{
    if (player1_wins >= STAGE_ROUNDS_TO_WIN) return 1;
    if (player2_wins >= STAGE_ROUNDS_TO_WIN) return 2;

    return 0;
}
