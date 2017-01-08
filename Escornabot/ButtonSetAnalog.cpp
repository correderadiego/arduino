// ButtonSetAnalog.cpp
/*

Copyright (C) 2014-2017 Escornabot - http://escornabot.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
USA.

See LICENSE.txt for details

*/

#include "ButtonSetAnalog.h"
#include "Configuration.h"
#include <Arduino.h>

#define PULLUP_VALUE 990

//////////////////////////////////////////////////////////////////////

ButtonSetAnalog::ButtonSetAnalog(const Config* config)
{
    this->_config = config;

    this->_val_btn_up = config->val_btn_up;
    this->_val_btn_right = config->val_btn_right;
    this->_val_btn_down = config->val_btn_down;
    this->_val_btn_left = config->val_btn_left;
    this->_val_btn_go = config->val_btn_go;
    this->_val_btn_reset = config->val_btn_reset;
}

//////////////////////////////////////////////////////////////////////

void ButtonSetAnalog::init()
{
    ButtonSet::init();
    pinMode(_config->pin_keypad, (_config->pullup ? INPUT_PULLUP : INPUT));
    _last_button = BUTTON_NONE;
}

//////////////////////////////////////////////////////////////////////

void ButtonSetAnalog::scanButtons()
{
    int16_t value = analogRead(_config->pin_keypad);
    int16_t diff, minor_diff;

    minor_diff = abs(value - PULLUP_VALUE);
    BUTTON button = BUTTON_NONE;

    diff = abs(value - _val_btn_up);
    if (diff < minor_diff)
    {
        minor_diff = diff;
        button = BUTTON_UP;
    }

    diff = abs(value - _val_btn_right);
    if (diff < minor_diff)
    {
        minor_diff = diff;
        button = BUTTON_RIGHT;
    }

    diff = abs(value - _val_btn_down);
    if (diff < minor_diff)
    {
        minor_diff = diff;
        button = BUTTON_DOWN;
    }

    diff = abs(value - _val_btn_left);
    if (diff < minor_diff)
    {
        minor_diff = diff;
        button = BUTTON_LEFT;
    }

    diff = abs(value - _val_btn_go);
    if (diff < minor_diff)
    {
        minor_diff = diff;
        button = BUTTON_GO;
    }

    diff = abs(value - _val_btn_reset);
    if (diff < minor_diff)
    {
        minor_diff = diff;
        button = BUTTON_RESET;
    }

    if (button != _last_button)
    {
        if (_last_button != BUTTON_NONE) released(_last_button);
        if (button != BUTTON_NONE) pressed(button);
        _last_button = button;
    }
}

//////////////////////////////////////////////////////////////////////

// EOF
