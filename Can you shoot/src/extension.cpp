#include "extension.h"

void DrawTexOrigin(Texture2D tex, Vector2 origin, float angle, Color c) {
    DrawTexturePro(tex, (Rectangle){ 0, 0, (float) tex.width, (float) tex.height }, (Rectangle){ origin.x, origin.y, (float) tex.width, (float) tex.height}, Vector2 {tex.width / 2.0f, tex.height / 2.0f}, angle, c);
}

void DrawTextCentered(Font font, const char* text, Vector2 origin, float size, Color c) {
    Vector2 textSize = MeasureTextEx(font, text, size, 0);
    DrawTextEx(font, text, Vector2{origin.x - textSize.x / 2, origin.y - textSize.y / 2}, size, 0, c);
}

int sgn(float val) {
    return (int)(val >= 0);
}

int GetRandomColor() {
    return (GetRandomValue(0, 0xFF) << 16) +
    (GetRandomValue(0, 0xFF) << 8) +
    GetRandomValue(0, 0xFF);
}

int Clamp0x00_0xFF(int v) {
    if (v < 0) return 0;
    if (v > 255) return 255;
    return v;
}