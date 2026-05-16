#pragma once

// Statystyki bazowe gracza, na które nakładają się StatModifiers.
// Ulepszenia (Upgrade) modyfikują albo to, albo modyfikatory.
struct PlayerStats {
    float baseMaxHealth   = 100.f;
    float baseMoveSpeed   = 150.f;
    float basePickupRadius = 40.f;
    int   gold            = 0;
    int   kills           = 0;
    float survivalTime    = 0.f; // sekundy przeżyte (wynik)
};
