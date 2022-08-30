#include "can.h"

#include <cmath>
#include "extension.h"

Can::Can(int x, int y)
{
    Can::tex = LoadTexture("./assets/can.png");
    Can::x = x;
    Can::y = y;
}

Can::~Can()
{
    UnloadTexture(Can::tex);
}

void Can::Update()
{
    Can::y += Can::accel;
    if (Can::accel < Can::terminalVelocity)
        Can::accel += Can::gravity;

    Can::x += Can::xSpeed;
    Can::rot *= 0.98;
    Can::angle += Can::rot;

    if (Can::x < Can::tex.width / 2) Can::xSpeed = abs(Can::xSpeed);
    if (Can::x > 1280 - Can::tex.width / 2) Can::xSpeed = -abs(Can::xSpeed);
}

void Can::Render()
{
    DrawTexOrigin(Can::tex, Vector2 { Can::x, Can::y }, Can::angle * PI, WHITE);
    // DrawCircle(Can::x, Can::y, 10, RED);
    // DrawRectangleLines(Can::x - Can::tex.height / 2, Can::y - Can::tex.height / 2, Can::tex.height, Can::tex.height, BLACK);
}

void Can::SetAccel(float accel)
{
    Can::accel = accel;
}

bool Can::ShotAt(int x, int y)
{
    if (x > Can::x - Can::tex.height / 2 && x < Can::x + Can::tex.height / 2 &&
        y > Can::y - Can::tex.height / 2 && y < Can::y + Can::tex.height / 2)
    {
        SetAccel(-10);
        Can::xSpeed = (Can::x - x) / 4;
        Can::rot = Can::xSpeed;
        return true;
    }
    return false;
}

float Can::GetAngle()
{
    return Can::angle;
}

void Can::Reset(int x, int y)
{
    Can::accel = 0;
    Can::xSpeed = 0;
    Can::rot = 0;
    Can::angle = 0;

    Can::x = x;
    Can::y = y;
}

bool Can::IsLost()
{
    return Can::y > 1000;
}