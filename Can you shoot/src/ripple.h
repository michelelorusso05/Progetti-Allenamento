#pragma once

#include "../include/raylib.h"

class Ripple {
public:
    Ripple(int _x, int _y, float duration, float targetSize, int color);

    void Update();
    void MarkForDeletion();
    bool MarkedForDeletion();

private:
    int x;
    int y;

    // In frames
    int duration = 0;
    int timer = 0;
    bool markForDeletion = false;

    float targetSize;
    int color;
};