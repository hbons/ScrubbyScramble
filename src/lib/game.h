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


extern const char* GAME_TITLE;
extern const char* GAME_CODE;
extern const char* GAME_VERSION;


#ifndef GAME_H
#define GAME_H

enum GameState {
    G_TITLE,
    G_ROUND_START,
    G_MAIN,
    G_ROUND_END,
    G_END,
};

#endif


extern enum GameMode GAME_MODE;
extern enum GameState GAME_STATE;
extern enum GameState PREV_GAME_STATE;


void game_init(void);
void game_update(void);

inline void game_state(enum GameState state);
bool game_state_changed_to(enum GameState state);
bool game_state_changed_from(enum GameState state);
