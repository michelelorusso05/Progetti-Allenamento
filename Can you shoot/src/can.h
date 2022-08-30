#pragma once

#include "../include/raylib.h"

class Can {
public:
    Can(int x, int y);
    ~Can();
    void Update();
    void Render();
    void SetAccel(float accel);
    bool ShotAt(int x, int y);
    void Reset(int x, int y);
    float GetAngle();

    bool IsLost();

private:
    float x;
    float y;
    const float gravity = 0.25;
    const float terminalVelocity = 104;
    float accel = 0;
    float xSpeed = 0;
    float angle = 0;
    float rot = 0;

    Texture2D tex;
};