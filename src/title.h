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


extern const palette_color_t P_LOGO[4];
extern const palette_color_t P_COPYRIGHT[4];

#define SPRITE_TITLE_ACORN 0
#define START_PRESSED_TIMEOUT 50


void title_init(void);
void title_init_tiles(void);
void title_update(void);
void title_draw(void);
void title_draw_logo(void);
void title_draw_acorn(void);
void title_draw_prompt(bool visible);
void title_draw_copyright(void);
