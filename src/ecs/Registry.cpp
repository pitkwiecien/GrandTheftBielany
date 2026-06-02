#include "ecs/Registry.hpp"

Entity Registry::create() {
    unsigned int id;
    if (!freeIds.empty()) {
        id = freeIds.back();
        freeIds.pop_back();
    }
    else {
        id = next++;
    }
    return Entity{id};
}

void Registry::destroy(Entity e) {
    if (!e.valid()) return;
    freeIds.push_back(e.id);
    for (auto& [_, pool] : pools)
        pool->remove(e.id);
}

void Registry::flushDestroyed() {
    for (Entity e : pendingDestroy)
        destroy(e);
    pendingDestroy.clear();
}
