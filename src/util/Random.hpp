#pragma once
#include <random>

class Random {
public:
    static int   range(int lo, int hi);
    static float range(float lo, float hi);
    static bool  chance(float p);
};
