#pragma once
#include <limits>

struct Entity {
    static constexpr unsigned int kInvalidId = std::numeric_limits<unsigned int>::max();
    unsigned int id = kInvalidId;

    bool valid() const { return id != kInvalidId; }
    bool operator==(const Entity& o) const { return id == o.id; }
};
