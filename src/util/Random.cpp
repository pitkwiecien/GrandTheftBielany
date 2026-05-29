#include "util/Random.hpp"

static std::mt19937 s_engine{std::random_device{}()};

std::mt19937& Random::engine() { return s_engine; }

void Random::seed(std::uint32_t s) { s_engine.seed(s); }

int Random::range(int lo, int hi) {
    std::uniform_int_distribution<int> dist(lo, hi);
    return dist(s_engine);
}

float Random::range(float lo, float hi) {
    std::uniform_real_distribution<float> dist(lo, hi);
    return dist(s_engine);
}

bool Random::chance(float p) {
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    return dist(s_engine) < p;
}

std::size_t Random::index(std::size_t size) {
    std::uniform_int_distribution<std::size_t> dist(0, size - 1);
    return dist(s_engine);
}
