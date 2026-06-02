#include "util/Random.hpp"

static std::mt19937 s_engine{std::random_device{}()};

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
