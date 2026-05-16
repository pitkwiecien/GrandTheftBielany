#pragma once

// Znajdźka na ziemi (XP gem, leczenie, magnes itp.).
enum class PickupKind { Experience, Health, Magnet, Gold };

struct PickupTag {
    PickupKind kind   = PickupKind::Experience;
    float      value  = 1.f;
    bool       attracted = false; // czy leci już do gracza (magnetyzm)
};
