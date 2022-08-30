#include "../include/raylib.h"

void DrawTexOrigin(Texture2D tex, Vector2 origin, float angle, Color c);
void DrawTextCentered(Font font, const char* text, Vector2 origin, float size, Color c);

int sgn(float val);

int GetRandomColor();

int Clamp0x00_0xFF(int v);