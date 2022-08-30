#include "ripple.h"
#include <cmath>

Ripple::Ripple(int _x, int _y, float duration, float targetSize, int color) {
    Ripple::x = _x;
    Ripple::y = _y;
    Ripple::duration = duration * 60;
    Ripple::targetSize = targetSize;
    Ripple::color = (color << 8) + 0x7F;
}

void Ripple::MarkForDeletion() {
    Ripple::markForDeletion = true;
}

bool Ripple::MarkedForDeletion() {
    return Ripple::markForDeletion;
}

void Ripple::Update() {
    if (Ripple::timer > duration) {
        Ripple::MarkForDeletion();
    }

    float m = sin(((float) timer / duration) * PI / 2);

    DrawCircle(Ripple::x, Ripple::y, (float) Ripple::targetSize * m, (GetColor(color - (float) 0x7F * m)));
    Ripple::timer++;
}