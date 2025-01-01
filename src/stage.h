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


extern const palette_color_t P_BKG_LIGHTS[4];
extern const palette_color_t P_BKG_DARKS[4];
extern const palette_color_t P_BKG_HUD[4];
extern const palette_color_t P_BKG_LEAVES[4];


extern const u8 STAGE_CANOPY_Y;
extern const u8 STAGE_GROUND_Y;
extern bool STAGE_BONUS_ACTIVE;

#define STAGE_ROUNDS_TO_WIN 2
#define STAGE_SCORE_PTS 1
#define STAGE_SCORE_PTS_BONUS 4


void stage_init(void);
void stage_init_tiles(void);
void stage_update(void);
void stage_draw(void);

void stage_check_collisions(struct Player* player);
u8 stage_get_winner(void);
