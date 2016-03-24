#pragma once

#include "pebble.h"

static const GPathInfo MINUTE_HAND_POINTS = {
    4, (GPoint []) {
        {-4, 0},
        {0, 15},
        {4, 0},
        {0, -80},
    }
};

static const GPathInfo HOUR_HAND_POINTS = {
    4, (GPoint []){
        {-4, 0},
        {0, 15},
        {4, 0},
        {0, -50},
        }
    };
