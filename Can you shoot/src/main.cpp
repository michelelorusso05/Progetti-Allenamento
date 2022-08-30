#include <iostream>
#include "../include/raylib.h"

#include <vector>
#include "ripple.h"
#include "can.h"
#include "extension.h"

int main()
{

    InitWindow(1280, 720, "Can you shoot?");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    HideCursor();

    SetTargetFPS(60);

    Font font = LoadFontEx("./assets/font.otf", 144, 0, NULL);
    Texture2D crosshair = LoadTexture("./assets/crosshair.png");

    std::vector<Ripple*> rippleList = std::vector<Ripple*>();
    Can* can = new Can(1280 / 2, 100);

    unsigned int score = 0;

    int gameOverTimer = 0;

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (can->ShotAt(GetMouseX(), GetMouseY())) 
            {
                rippleList.push_back(new Ripple(GetMouseX(), GetMouseY(), 0.35f, 150, GetRandomColor()));
                score++;
            }
            else
                rippleList.push_back(new Ripple(GetMouseX(), GetMouseY(), 0.35f, 75, 0x7F7F7F));
        }
        if (IsKeyDown(KEY_R)) {
            can->Reset(1280 / 2, 100);
            score = 0;
            gameOverTimer = 0;
        }

        can->Update();

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTextCentered(font, TextFormat("%d", score), Vector2 {1280 / 2, 720 / 2}, 144, GetColor(0x7F7F7F7F));
            
            can->Render();

            DrawRectangleGradientV(0, 720 / 2 + 720 / 4, 1280, 720 / 4, GetColor(0x00000000), GetColor(0x0000003F));
            // Ripple update
            for (int i = rippleList.size() - 1; i >= 0; i--)
            {
                rippleList.at(i)->Update();
                if (rippleList.at(i)->MarkedForDeletion()) {
                    delete rippleList.at(i);
                    rippleList.erase(rippleList.begin() + i);
                }
            }

            DrawTexOrigin(crosshair, GetMousePosition(), can->GetAngle() * PI, WHITE);
            
            if (can->IsLost()) {
                if (gameOverTimer < 2 << 16)
                    gameOverTimer += 16;

                DrawTextCentered(font, "The can was then doomed to fall forever...", Vector2{640, 200}, 72, GetColor(0x7F7F7F00 + Clamp0x00_0xFF(gameOverTimer)));
                DrawTextCentered(font, "Press R to restart.", Vector2{640, 250}, 48, GetColor(0x7F7F7F00 + Clamp0x00_0xFF(gameOverTimer - 512)));
            }

        EndDrawing();

    }

    delete can;
    UnloadFont(font);

    CloseWindow();
    return 0;
}