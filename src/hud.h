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


#define SPRITE_HUD_MARKER 30

#define TILE_HUD_EMPTY 0
#define TILE_HUD_HOG_1 2
#define TILE_HUD_HOG_2 1

#define TILE_HUD_MARKER_LITE 0
#define TILE_HUD_MARKER_DARK 1

#define HUD_SCORE_WIN 15
extern u8 HUD_SCORE_1;
extern u8 HUD_SCORE_2;


void hud_init(void);
void hud_init_tiles(void);
void hud_update(void);
void hud_update_score(u8 score1, u8 score2);
void hud_draw(void);
void hud_draw_empty(void);
void hud_draw_score_1(bool visible);
void hud_draw_score_2(bool visible);
void hud_draw_blink(void);
void hud_draw_marker(void);
