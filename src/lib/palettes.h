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


#include "colors.h"
#include "headers.h"


#define N_BKG_PALETTES 4
#define N_SPR_PALETTES 4

#define S_PALETTE_1 0b00000000
#define S_PALETTE_2 0b00000001
#define S_PALETTE_3 0b00000010
#define S_PALETTE_4 0b00000011


extern const palette_color_t P_CLEAR[4];
extern const palette_color_t P_FONT[4];


void palettes_init_bkg(const palette_color_t *p1, const palette_color_t *p2,
                       const palette_color_t *p3, const palette_color_t *p4);

void palettes_init_sprite(const palette_color_t *p1, const palette_color_t *p2,
                          const palette_color_t *p3, const palette_color_t *p4);

void palettes_clear(void);
void palettes_clear_bkg(void);
void palettes_clear_sprite(void);
