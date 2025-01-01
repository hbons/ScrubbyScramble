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


#include "extensions.h"


// Use even numbers to aid /2 division!
void fill_attr_rect(u8 x, u8 y, u8 w, u8 h, u8 attrs)
{
    for (u8 i = 0; i != w; i++)
        for (u8 j = 0; j != h; j++)
            set_bkg_attribute_xy(x + i, y + j, attrs);
}
