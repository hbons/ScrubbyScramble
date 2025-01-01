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


#include "game.h"
#include "util.h"


const char* GAME_TITLE = "SCRUBBY SCRAMBLE";
const char* GAME_CODE = "NES-SCRB-EUR";
const char* GAME_VERSION = "0.1";

enum GameState GAME_STATE;
enum GameState PREV_GAME_STATE;


void game_init(void)
{
    GAME_STATE = G_TITLE;
    PREV_GAME_STATE = G_TITLE;
}


void game_update(void)
{
    if (GAME_STATE != PREV_GAME_STATE)
        PREV_GAME_STATE = GAME_STATE;
}


inline void game_state(enum GameState state)
{
    GAME_STATE = state;
}


bool game_state_changed_to(enum GameState state)
{
    return (GAME_STATE == state) &&
           (GAME_STATE != PREV_GAME_STATE);
}

bool game_state_changed_from(enum GameState state)
{
    return (PREV_GAME_STATE == state) &&
           (GAME_STATE != PREV_GAME_STATE);
}
