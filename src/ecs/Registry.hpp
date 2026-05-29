#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Entity.hpp"
#include "ComponentPool.hpp"

class Registry {
public:
    Entity create();
    void destroy(Entity e);
    bool alive(Entity e) const;
    void queueDestroy(Entity e) { pendingDestroy.push_back(e); }
    void flushDestroyed();
    std::size_t aliveCount() const;

    template <typename T, typename... Args>
    T& add(Entity e, Args&&... args) {
        return pool<T>().emplace(e.id, std::forward<Args>(args)...);
    }

    template <typename T>
    void remove(Entity e) {
        if (auto* p = tryPool<T>()) p->remove(e.id);
    }

    template <typename T>
    T* tryGet(Entity e) {
        auto* p = tryPool<T>();
        return p ? p->tryGet(e.id) : nullptr;
    }

    template <typename T>
    bool has(Entity e) {
        auto* p = tryPool<T>();
        return p && p->has(e.id);
    }

    template <typename First, typename... Rest, typename Fn>
    void view(Fn&& fn) {
        auto* first = tryPool<First>();
        if (!first) return;
        first->each([&](std::uint32_t id, First& f) {
            if ((has<Rest>(Entity{id, 0}) && ...)) {
                Entity e{id, id < generations.size() ? generations[id] : 0u};
                fn(e, f, *tryPool<Rest>()->tryGet(id)...);
            }
        });
    }

private:
    template <typename T>
    ComponentPool<T>& pool() {
        std::type_index ti(typeid(T));
        auto it = pools.find(ti);
        if (it == pools.end()) {
            auto p = std::make_unique<ComponentPool<T>>();
            auto* raw = p.get();
            pools.emplace(ti, std::move(p));
            return *raw;
        }
        return *static_cast<ComponentPool<T>*>(it->second.get());
    }

    template <typename T>
    ComponentPool<T>* tryPool() {
        auto it = pools.find(std::type_index(typeid(T)));
        if (it == pools.end()) return nullptr;
        return static_cast<ComponentPool<T>*>(it->second.get());
    }

    std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> pools;
    std::vector<std::uint32_t> generations;
    std::vector<std::uint32_t> freeIds;
    std::uint32_t next = 0;
    std::vector<Entity> pendingDestroy;
};
