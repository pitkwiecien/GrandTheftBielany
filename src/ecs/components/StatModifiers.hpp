#pragma once

// Mnożniki nakładane przez ulepszenia (level-up).
// Systemy mnożą wartości bazowe przez te pola.
struct StatModifiers {
    float damageMult    = 1.f;
    float moveSpeedMult  = 1.f;
    float cooldownMult   = 1.f; // <1 = szybsze strzelanie
    float pickupRadiusMult = 1.f;
    float projectileSpeedMult = 1.f;
    float maxHealthMult  = 1.f;
    float xpGainMult     = 1.f;
    int   extraProjectiles = 0;
};
