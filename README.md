# Grand Theft Bielany

Prosta strzelanka 2D z widokiem z góry napisana w C++17 i SDL2. Gracz odpiera kolejne fale dzików, zbiera apteczki i eliminuje przeciwników za pomocą strzelby. Projekt wykorzystuje architekturę ECS (Entity Component System).

---

## Autorzy

* Piotr Kwiecień
* Mikołaj Urbańczyk
* Bartosz Pawłowski

---

## Kompilacja

Instalacja zależności:

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

Budowanie projektu:

```bash
cmake -B build
cmake --build build
./build/bin/gtb
```

---

## Architektura ECS

### Entity

`Entity` jest identyfikatorem obiektu w grze i nie przechowuje żadnych danych ani logiki.

### Components

Komponenty opisują dane przypisane do encji:

* `Transform` - pozycja i obrót
* `Velocity` - ruch obiektu
* `Health` - punkty życia
* `Collider` - obsługa kolizji
* `SpriteComp` - dane renderowania
* `DirectionComp` - kierunek postaci
* `AnimationComp` - stan animacji
* `PlayerTag` - oznaczenie gracza
* `EnemyTag` - oznaczenie przeciwnika
* `ProjectileTag` - dane pocisku
* `BeerPickup` - przedmiot leczący

### Registry

`Registry` zarządza encjami, komponentami oraz ich bezpiecznym usuwaniem. Umożliwia tworzenie obiektów, dodawanie komponentów i iterację po wybranych zestawach danych.

### Systems

Logika gry została podzielona na niezależne systemy:

1. `PlayerInputSystem` - obsługa sterowania
2. `EnemyAISystem` - zachowanie przeciwników
3. `MovementSystem` - ruch obiektów
4. `SeparationSystem` - rozdzielanie nakładających się encji
5. `ContactDamageSystem` - zadawanie obrażeń przy kontakcie
6. `ShootingSystem` - tworzenie pocisków
7. `ProjectileSystem` - obsługa pocisków
8. `PickupSystem` - zbieranie apteczek
9. `AnimationSystem` - aktualizacja animacji

Systemy komunikują się wyłącznie przez komponenty przechowywane w `Registry`, dzięki czemu kod pozostaje prosty i łatwy w rozbudowie.
