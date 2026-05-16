#pragma once
#include <random>
#include <cstdint>

// Globalny generator losowy gry. Wrapper na <random>,
// żeby cały kod losował spójnie i dało się ustawić seed.
class Random {
public:
    // Inicjalizacja pojedynczego globalnego silnika.
    static void seed(std::uint32_t s);

    // Liczba całkowita z przedziału [lo, hi] (włącznie).
    static int range(int lo, int hi);

    // Liczba zmiennoprzecinkowa z przedziału [lo, hi).
    static float range(float lo, float hi);

    // true z prawdopodobieństwem p (0..1).
    static bool chance(float p);

    // Losowy indeks 0..size-1 (np. wybór wroga z listy).
    static std::size_t index(std::size_t size);

private:
    static std::mt19937& engine();
};
