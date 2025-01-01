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


#include <nes/nes.h>

#include "lib/clock.h"
#include "lib/font.h"
#include "lib/game.h"
#include "lib/joypad.h"
#include "lib/tileset.h"
#include "lib/util.h"

#include "main.h"
#include "round.h"
#include "stage.h"
#include "title.h"

#include "lib/palettes.h"
#include "lib/extensions.h"


void main(void)
{
    palettes_clear();
    vsync();

    init();
    title_init();
    title_init_tiles();

    while(GAME_STATE == G_TITLE) {
        update();
        title_update();
        title_draw();
        vsync();
    }

    // Show the round already to hide the stage load
    update();
    draw();

    stage_init();
    stage_init_tiles();
    round_init();

    while(true) {
        update();
        draw();
        vsync();
    }
}


void init(void)
{
    game_init();
    joypad_init_multi(2);
    tileset_init();
    font_init();
}


void update(void)
{
    game_update();
    clock_update();
    joypad_update();

    if (GAME_STATE == G_MAIN ||
        GAME_STATE == G_ROUND_END) {
        stage_update();
    }

    if (GAME_STATE == G_ROUND_START ||
        GAME_STATE == G_END) {
        round_update();
    }
}


void draw(void)
{
    if (GAME_STATE == G_MAIN ||
        GAME_STATE == G_ROUND_END) {
        stage_draw();
    }

    if (GAME_STATE == G_ROUND_START ||
        GAME_STATE == G_END) {
        round_draw();
    }
}
