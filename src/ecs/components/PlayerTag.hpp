#pragma once

// Znacznik encji gracza. Trzyma też progresję poziomów.
struct PlayerTag {
    int   level        = 1;
    float experience   = 0.f;   // bieżące XP w obecnym poziomie
    float xpToNextLevel = 5.f;  // próg awansu (rośnie z poziomem)
    int   pendingLevelUps = 0;  // ile ekranów wyboru ulepszeń czeka
};
