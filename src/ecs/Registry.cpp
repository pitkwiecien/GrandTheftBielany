#include "ecs/Registry.hpp"

Entity Registry::create() {
    uint32_t id;
    if (!freeIds.empty()) {
        id = freeIds.back();
        freeIds.pop_back();
    }
    else {
        id = next++;
        generations.push_back(0);
    }
    return Entity{id, generations[id]};
}

bool Registry::alive(Entity e) const {
    return e.id < generations.size()
        && generations[e.id] == e.gen;
}

void Registry::destroy(Entity e) {
    if (!alive(e))
        return;
    ++generations[e.id];
    freeIds.push_back(e.id);
    for (auto& [_, pool] : pools)
        pool->remove(e.id);
}

void Registry::flushDestroyed() {
    for (Entity e : pendingDestroy)
        destroy(e);
    pendingDestroy.clear();
}

std::size_t Registry::aliveCount() const {
    return next - freeIds.size();
}