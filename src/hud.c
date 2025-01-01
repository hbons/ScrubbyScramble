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
#include "lib/extensions.h"
#include "lib/palettes.h"
#include "lib/tileset.h"

#include "hud.h"

#include "../res/hud.h"
#include "../res/player.h"


u8 HUD_SCORE_1;
u8 HUD_SCORE_2;

static u8 TILE_SPR_0;
static u8 TILE_BKG_0;

static bool needs_redraw;
static bool needs_blink_redraw;


void hud_init(void)
{
    HUD_SCORE_1 = 0;
    HUD_SCORE_2 = 0;

    needs_redraw = true;
    needs_blink_redraw = false;
}


void hud_init_tiles(void)
{
    TILE_BKG_0 = tileset_init_bkg_tiles(hud_TILE_COUNT, hud_tiles);
    TILE_SPR_0 = tileset_init_sprite_tiles(2, player_tiles + TILE_OFFSET(12));
}


void hud_update(void)
{
    if (needs_blink_redraw)
        return;

    if (HUD_SCORE_1 >= HUD_SCORE_WIN ||
        HUD_SCORE_2 >= HUD_SCORE_WIN) {
        needs_blink_redraw = true;
    }
}


void hud_update_score(u8 score1, u8 score2)
{
    HUD_SCORE_1 = score1;
    HUD_SCORE_2 = score2;

    needs_redraw = true;
}


#define SCORE_X 2
#define SCORE_Y 26
#define SCORE_W 28
#define SCORE_H 2

void hud_draw(void)
{
    if (needs_blink_redraw) {
        hud_draw_blink();
        hud_draw_marker();
        goto end;
    }

    if (!needs_redraw)
        return;

    hud_draw_empty();
    hud_draw_score_1(true);
    hud_draw_score_2(true);
    hud_draw_marker();

    fill_attr_rect(SCORE_X, SCORE_Y, SCORE_W, SCORE_H, S_PALETTE_4);

    end:
    needs_redraw = false;
}


void hud_draw_empty(void)
{
    for (u8 i = 0; i != SCORE_W; i++)
        set_bkg_tile_xy(SCORE_X + i, SCORE_Y, TILE_BKG(TILE_HUD_EMPTY));
}

void hud_draw_score_1(bool visible)
{
    u8 tile = visible ? TILE_HUD_HOG_1 : TILE_HUD_EMPTY;

    for (u8 i = 0; i != HUD_SCORE_1; i++)
        set_bkg_tile_xy(SCORE_X + i, SCORE_Y, TILE_BKG(tile));
}

void hud_draw_score_2(bool visible)
{
    u8 tile = visible ? TILE_HUD_HOG_2 : TILE_HUD_EMPTY;

    for (u8 i = 0; i != HUD_SCORE_2; i++)
        set_bkg_tile_xy(SCORE_X + SCORE_W - i - 1, SCORE_Y, TILE_BKG(tile));
}


void hud_draw_blink(void)
{
    bool blink_visible = CLOCK_INTERVAL_16;

    if (HUD_SCORE_1 >= HUD_SCORE_WIN)
        hud_draw_score_1(blink_visible);

    if (HUD_SCORE_2 >= HUD_SCORE_WIN)
        hud_draw_score_2(blink_visible);
}


#define MARKER_X 124
#define MARKER_Y 216

void hud_draw_marker(void)
{
    u8 tile = TILE_HUD_MARKER_LITE;
    u8 palette = S_PALETTE_3;

    if (HUD_SCORE_1 >= HUD_SCORE_WIN) {
        tile = TILE_HUD_MARKER_DARK;
        palette = S_PALETTE_1;
    }

    if (HUD_SCORE_2 >= HUD_SCORE_WIN) {
        tile = TILE_HUD_MARKER_DARK;
        palette = S_PALETTE_2;
    }

    set_sprite_tile(SPRITE_HUD_MARKER, TILE_SPR(tile));
    set_sprite_prop(SPRITE_HUD_MARKER, palette);
    move_sprite(SPRITE_HUD_MARKER, MARKER_X, MARKER_Y);
}
