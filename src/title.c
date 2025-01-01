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
#include "lib/extensions.h"
#include "lib/font.h"
#include "lib/game.h"
#include "lib/joypad.h"
#include "lib/palettes.h"
#include "lib/tileset.h"
#include "lib/util.h"

#include "acorn.h"
#include "round.h"
#include "title.h"

#include "../res/logo.h"
#include "../res/drops.h"


const palette_color_t P_LOGO[4] = {
    C_COMMON, C_PURPLE_2, C_TEAL_2, C_CYAN_1 };

const palette_color_t P_COPYRIGHT[4] = {
    C_COMMON, C_BLACK, C_BLACK, C_CYAN_1 };


static bool needs_redraw;

bool start_pressed;
u8 start_pressed_timer;

static u8 TILE_BKG_0;


void title_init(void)
{
    needs_redraw = true;

    start_pressed = false;
    start_pressed_timer = START_PRESSED_TIMEOUT;
}


void title_init_tiles(void)
{
    TILE_BKG_0 = tileset_init_bkg_tiles(logo_TILE_COUNT, logo_tiles);
}


void title_update(void)
{
    if (joypad_button_released(J_PAD_1, J_START) ||
        joypad_button_released(J_PAD_1, J_A)) {
        start_pressed = true;
        initrand(SYS_CLOCK.ticks);
    }

    if (start_pressed)
        start_pressed_timer--;

    if (start_pressed_timer == 0) {
        palettes_clear(); // Fastest way to visibly clear the screen
        util_hide_sprites();
        util_clear_bkg();

        round_init();
        game_state(G_ROUND_START);
        round_update();
    }
}


void title_draw(void)
{
    if (start_pressed) // Flash the prompt
        title_draw_prompt(CLOCK_INTERVAL_4);
    else
        title_draw_prompt(CLOCK_INTERVAL_32);

    if (!needs_redraw)
        return;

    title_draw_logo();
    title_draw_copyright();
    title_draw_acorn();

    palettes_init_bkg(P_FONT, P_COPYRIGHT, P_LOGO, P_CLEAR);
    palettes_init_sprite(P_ACORN, P_ACORN, P_ACORN, P_ACORN);

    needs_redraw = false;
}


const u8 LOGO_COL = 7;
const u8 LOGO_ROW = 7;
const u8 LOGO_W = 18;
const u8 LOGO_H = 4;

const u8 LOGO_WORD_OFFSET = 24;
const u8 LOGO_WORD_PAD = 3;

void title_draw_logo(void)
{
    u8 col = 0;
    u8 row = 0;

    fill_attr_rect(LOGO_COL, LOGO_ROW, LOGO_W, LOGO_H, S_PALETTE_3);

    for (u8 i = 0; i != (logo_TILE_COUNT - 34); i++) {
        u8 tile = TILE_BKG(i);

        if (i < LOGO_WORD_OFFSET)
            set_bkg_tile_xy(LOGO_COL + col, // "scrubby"
                            LOGO_ROW + row,
                            tile);

        set_bkg_tile_xy(LOGO_COL + col + LOGO_WORD_PAD, // "scramble"
                        LOGO_ROW + row + LOGO_WORD_PAD,
                        LOGO_WORD_OFFSET + tile);

        if (row == 0)
            row = 1;
        else {
            row = 0;
            col++;
        }
    }

    // Ascenders "bb"
    set_bkg_tile_xy(LOGO_COL + 7,  LOGO_ROW - 1, TILE_BKG(56));
    set_bkg_tile_xy(LOGO_COL + 8,  LOGO_ROW - 1, TILE_BKG(58));
    set_bkg_tile_xy(LOGO_COL + 9,  LOGO_ROW - 1, TILE_BKG(60));

    // Descencer "y"
    set_bkg_tile_xy(LOGO_COL + 10, LOGO_ROW + 2, TILE_BKG(57));
    set_bkg_tile_xy(LOGO_COL + 11, LOGO_ROW + 2, TILE_BKG(59));

    // Ascenders "bl"
    set_bkg_tile_xy(LOGO_COL + 12, LOGO_ROW + 2, TILE_BKG(52));
    set_bkg_tile_xy(LOGO_COL + 13, LOGO_ROW + 2, TILE_BKG(54));
    set_bkg_tile_xy(LOGO_COL + 14, LOGO_ROW + 2, TILE_BKG(53));
    set_bkg_tile_xy(LOGO_COL + 15, LOGO_ROW + 2, TILE_BKG(55));

    // Copyright
    set_bkg_tile_xy(LOGO_COL + 17, LOGO_ROW + 2, TILE_BKG(61));
}


#define TILE_ACORN_TMP 0x00

void title_draw_acorn(void)
{
    // Use temporary tile and sprite. Will be overwritten later
    set_sprite_data(TILE_ACORN, 1, drops_tiles);
    set_sprite_tile(SPRITE_TITLE_ACORN, TILE_ACORN_TMP);
    move_sprite(SPRITE_TITLE_ACORN, 192, 92);
}


const u8 PROMPT_COL = 11;
const u8 PROMPT_ROW = 16;
const u8 PROMPT_W = 10;
const u8 PROMPT_H = 2;

const char* prompt_label_on  = "PUSH START";
const char* prompt_label_off = "          ";

void title_draw_prompt(bool visible)
{
    fill_attr_rect(PROMPT_COL, PROMPT_ROW,
                   PROMPT_W, PROMPT_H,
                   S_PALETTE_1);

    font_print_chars(PROMPT_COL, PROMPT_ROW,
        visible ? (char*)prompt_label_on : (char*)prompt_label_off);
}


const u8 COPYRIGHT_COL = 3;
const u8 COPYRIGHT_ROW = 22;
const u8 COPYRIGHT_W = 26;
const u8 COPYRIGHT_H = 6;

const char* copyright_label_1 = "    @ 2024 HYLKE BONS";
const char* copyright_label_2 = " FREE TO ENJOY REMIX SHARE";
const char* copyright_label_3 = "CREATIVE COMMONS BY-NC-SA 4";

void title_draw_copyright(void)
{
    fill_attr_rect(COPYRIGHT_COL, COPYRIGHT_ROW,
                   COPYRIGHT_W, COPYRIGHT_H,
                   S_PALETTE_2);

    font_print_chars(COPYRIGHT_COL, COPYRIGHT_ROW,     (char*)copyright_label_1);
    font_print_chars(COPYRIGHT_COL, COPYRIGHT_ROW + 2, (char*)copyright_label_2);
    font_print_chars(COPYRIGHT_COL, COPYRIGHT_ROW + 4, (char*)copyright_label_3);
}
