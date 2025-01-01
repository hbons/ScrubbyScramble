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


#include "headers.h"


#ifndef FONT_H
#define FONT_H
#endif


void font_init(void);
u8 font_tile_for_char(char* c);
void font_print_chars(u8 x, u8 y, char* chars);

extern u8 TILE_A;
#define TILE_B (TILE_A + 1)
#define TILE_C (TILE_A + 2)
#define TILE_D (TILE_A + 3)
#define TILE_E (TILE_A + 4)
#define TILE_F (TILE_A + 5)
#define TILE_G (TILE_A + 6)
#define TILE_H (TILE_A + 7)
#define TILE_I (TILE_A + 8)
#define TILE_J (TILE_A + 9)
#define TILE_K (TILE_A + 10)
#define TILE_L (TILE_A + 11)
#define TILE_M (TILE_A + 12)
#define TILE_N (TILE_A + 13)
#define TILE_O (TILE_A + 14)
#define TILE_P (TILE_A + 15)
#define TILE_Q (TILE_A + 16)
#define TILE_R (TILE_A + 17)
#define TILE_S (TILE_A + 18)
#define TILE_T (TILE_A + 19)
#define TILE_U (TILE_A + 20)
#define TILE_V (TILE_A + 21)
#define TILE_W (TILE_A + 22)
#define TILE_X (TILE_A + 23)
#define TILE_Y (TILE_A + 24)
#define TILE_Z (TILE_A + 25)

#define TILE_0 (TILE_Z + 1)
#define TILE_1 (TILE_0 + 1)
#define TILE_2 (TILE_0 + 2)
#define TILE_3 (TILE_0 + 3)
#define TILE_4 (TILE_0 + 4)
#define TILE_5 (TILE_0 + 5)
#define TILE_6 (TILE_0 + 6)
#define TILE_7 (TILE_0 + 7)
#define TILE_8 (TILE_0 + 8)
#define TILE_9 (TILE_0 + 9)

#define TILE_CHAR_SPACE (TILE_9 + 1)
// #define TILE_CHAR_DOT (TILE_9 + 2)
// #define TILE_CHAR_COLON (TILE_9 + 3)
// #define TILE_CHAR_PERCENT (TILE_9 + 4)
#define TILE_CHAR_COPYRIGHT (TILE_9 + 2) // '@'
// #define TILE_CHAR_MULTIPLY (TILE_9 + 6) // '*'
// #define TILE_CHAR_SLASH (TILE_9 + 7)
#define TILE_CHAR_DASH (TILE_9 + 3)
#define TILE_CHAR_EXCLAMATION (TILE_9 + 4)
