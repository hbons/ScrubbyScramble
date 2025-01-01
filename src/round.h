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


extern u8 ROUND;

#define ROUND_TIMEOUT 120
#define ROUND_END_TIMEOUT 255

extern const palette_color_t P_FONT_GREEN[4];
extern const palette_color_t P_FONT_PURPLE[4];


void round_init(void);
void round_update(void);
void round_draw(void);
void round_draw_ending(void);
void round_draw_ending_hedgehogs(void);
void round_draw_ending_leaves(void);
