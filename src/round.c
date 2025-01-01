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
#include "lib/clock.h"
#include "lib/extensions.h"
#include "lib/font.h"
#include "lib/game.h"
#include "lib/joypad.h"
#include "lib/palettes.h"
#include "lib/util.h"

#include "acorn.h"
#include "background.floor.h"
#include "leaves.h"
#include "player.h"
#include "round.h"
#include "stage.h"


u8 ROUND;
static u8 round_timer;
static u8 round_end_timer;

static bool needs_redraw;

void round_init(void)
{
    ROUND = 0;
    round_timer = ROUND_TIMEOUT;
    round_end_timer = ROUND_END_TIMEOUT;

    needs_redraw = false;
}


void round_update(void)
{
    if (game_state_changed_to(G_ROUND_START) ||
        game_state_changed_to(G_END)) {

        ROUND++;
        round_timer = ROUND_TIMEOUT;
        needs_redraw = true;
    }

    if (GAME_STATE == G_ROUND_START) {
        round_timer--;

        if (round_timer == 0) {
            util_clear_bkg();
            util_hide_sprites();
            palettes_clear_bkg();
            vsync();

            initrand(SYS_CLOCK.ticks);
            game_state(G_MAIN);
        }
    }

    if (stage_get_winner() != 0)
        game_state(G_END);

    if (GAME_STATE == G_END) {
        if (round_end_timer == 0)
            util_system_reset();

        round_end_timer--;
    }
}


const char* ROUND_LABEL = "ROUND";

void round_draw(void)
{
    if (!needs_redraw)
        return;

    util_clear_bkg();
    util_hide_sprites();

    palettes_init_bkg(P_FONT, P_FONT_GREEN, P_FONT_PURPLE, P_BKG_HUD);
    fill_attr_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, S_PALETTE_1);

    if (GAME_STATE == G_END) {
        round_draw_ending();
        goto end;
    }

    u8 x = 12;
    u8 y = 14;

    font_print_chars(x, y, (char*)ROUND_LABEL);
    set_bkg_tile_xy(x + 6, y, TILE_0 + ROUND);

    end:
    needs_redraw = false;
}


const char* ROUND_END_LABEL_GREEN  = "CONGRATS GREEN!";
const char* ROUND_END_LABEL_PURPLE = "CONGRATS PURPLE!";

const palette_color_t P_FONT_GREEN[4] = {
    C_COMMON, C_TEAL_2, C_TEAL_2, C_TEAL_2 };

const palette_color_t P_FONT_PURPLE[4] = {
    C_COMMON, C_PURPLE_2, C_PURPLE_2, C_PURPLE_2 };

void round_draw_ending(void)
{
    const u8 col = 8;
    const u8 row = 14;

    const char* color_label = ROUND_END_LABEL_GREEN;
    const palette_color_t *palette1 = P_HEDGEHOG_2;
    const palette_color_t *palette2 = P_HEDGEHOG_1;

    // Swap palettes based on the winner
    palette_color_t palette = S_PALETTE_2;

   if (stage_get_winner() == 2) {
        palette = S_PALETTE_3;
        color_label = ROUND_END_LABEL_PURPLE;
        palette1 = P_HEDGEHOG_1;
        palette2 = P_HEDGEHOG_2;
    }

    // Text
    font_print_chars(col, row, (char*)color_label);
    fill_attr_rect(col + 8, row, 8, 2, palette);
    palettes_init_sprite(palette1, palette2, P_ACORN, P_LEAVES);

    // Grass
    fill_attr_rect(col + 3,  row - 2, 1, 1, S_PALETTE_4);
    fill_attr_rect(col + 12, row - 2, 1, 1, S_PALETTE_4);
    background_draw_grass(col + 12, row - 2,
                          col + 3,  row - 2);

    round_draw_ending_hedgehogs();
    round_draw_ending_leaves();
}


void round_draw_ending_hedgehogs(void)
{
    // player_init(); // Already done by stage_init()

    player1.x = 99;
    player1.y = 87;
    player1.direction = DIRECTION_RIGHT;
    player1.wink = true;

    player2.x = 128;
    player2.y = 87;
    player2.direction = DIRECTION_LEFT;
    player2.wink = true;

    player_draw();
}


void round_draw_ending_leaves(void)
{
    leaves_init(); // Reset possibly shaded leaves

    // Lower sprite numbers to draw on top
    leaves[1].sprite = 0;
    leaves[2].sprite = 1;

    // Change tile order
    set_sprite_tile(leaves[0].sprite, TILE_SPR_LEAVES_0 + leaves[1].tile);
    set_sprite_tile(leaves[1].sprite, TILE_SPR_LEAVES_0 + leaves[0].tile);
    set_sprite_tile(leaves[2].sprite, TILE_SPR_LEAVES_0 + leaves[2].tile);

    set_sprite_prop(leaves[0].sprite, S_PALETTE_4 | S_FLIPX);
    set_sprite_prop(leaves[1].sprite, S_PALETTE_4);
    set_sprite_prop(leaves[2].sprite, S_PALETTE_4);

    move_sprite(leaves[0].sprite, 125, 95); // Red
    move_sprite(leaves[1].sprite, 139, 87); // Yellow
    move_sprite(leaves[2].sprite, 149, 95); // Orange
}
