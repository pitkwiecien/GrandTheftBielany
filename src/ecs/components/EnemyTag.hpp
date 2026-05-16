#pragma once

// Znacznik wroga. xpReward = ile XP wypada po śmierci,
// touchDamage = obrażenia zadawane graczowi przy kontakcie.
struct EnemyTag {
    int   typeId      = 0;
    float touchDamage = 1.f;
    float xpReward    = 1.f;
    float contactCooldown = 0.f; // throttling obrażeń kontaktowych
};
