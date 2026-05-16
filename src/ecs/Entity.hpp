#pragma once
#include <cstdint>

// Encja to lekki identyfikator. Wersja (generation) chroni
// przed użyciem nieaktualnego uchwytu po recyklingu indeksu.
struct Entity {
    std::uint32_t id  = kInvalidId;
    std::uint32_t gen = 0;

    static constexpr std::uint32_t kInvalidId = 0xFFFFFFFF;

    bool valid() const { return id != kInvalidId; }

    bool operator==(const Entity& o) const {
        return id == o.id && gen == o.gen;
    }
    bool operator!=(const Entity& o) const { return !(*this == o); }
};

inline constexpr Entity kNullEntity{};
