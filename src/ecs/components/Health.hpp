#pragma once

// Punkty życia. invulnTimer daje krótką nietykalność po trafieniu
// (typowe w survivorach, by gracz nie tracił całego HP w jednej klatce).
struct Health {
    float current     = 1.f;
    float max         = 1.f;
    float invulnTimer = 0.f; // sekundy pozostałej nietykalności
    bool  dead        = false;

    void damage(float amount) {
        if (invulnTimer > 0.f || dead) return;
        current -= amount;
        if (current <= 0.f) { current = 0.f; dead = true; }
    }

    void heal(float amount) {
        if (dead) return;
        current = (current + amount > max) ? max : current + amount;
    }
};
