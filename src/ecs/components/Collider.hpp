#pragma once

// Kolizja kołowa — w survivorze setki encji, koło vs koło
// jest najtańsze i wystarczająco dokładne.
struct Collider {
    float radius = 8.f;
    bool  trigger = false; // true => wykrywa, ale nie blokuje (pickupy)
};
