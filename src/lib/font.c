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


#include "font.h"
#include "../../res/font.h"


u8 TILE_A;

void font_init(void)
{
    // Load the font at the end of tile memory
    u8 last_tile = 0xff;
    TILE_A = last_tile - font_TILE_COUNT;
    set_bkg_data(TILE_A, font_TILE_COUNT, font_tiles);
}


u8 font_tile_for_char(char* c)
{
    u8 tile;

    switch (*c)
    {
        default:
            if (*c >= 'A') { // Letters
                u8 case_shift = 0;

                if (*c >= 'a') // Treat all as uppercase
                    case_shift = 32;

                tile = TILE_A + (*c - 'A') - case_shift;
                goto end;
            }

            if (*c >= '0') { // Numbers
                tile = TILE_0 + (*c - '0');
                goto end;
            }

            tile = (u8)TILE_CHAR_DASH; // Default
            goto end;

        case ' ': tile = (u8)TILE_CHAR_SPACE; break;
        // case '.': tile = (u8)TILE_CHAR_DOT; break;
        // case ':': tile = (u8)TILE_CHAR_COLON; break;
        // case '%': tile = (u8)TILE_CHAR_PERCENT; break;
        case '@': tile = (u8)TILE_CHAR_COPYRIGHT; break;
        // case '*': tile = (u8)TILE_CHAR_MULTIPLY; break;
        // case '/': tile = (u8)TILE_CHAR_SLASH; break;
        case '-': tile = (u8)TILE_CHAR_DASH; break;
        case '!': tile = (u8)TILE_CHAR_EXCLAMATION; break;
    }

    end:
    return tile;
}


void font_print_chars(u8 x, u8 y, char* chars)
{
    for (u8 i = 0; chars[i] != '\0'; i += 1) {
        u8 tile = font_tile_for_char(&chars[i]);
        set_bkg_tile_xy(x, y, tile);
        x++;
    }
}
