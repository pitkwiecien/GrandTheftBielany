#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Entity.hpp"
#include "ComponentPool.hpp"

// Serce ECS. Tworzy/niszczy encje i zarządza pulami komponentów.
// Iteracja: view<A, B>([](Entity e, A& a, B& b){ ... }).
class Registry {
public:
    Entity create();
    void   destroy(Entity e);
    bool   alive(Entity e) const;

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

    // Iteracja po encjach mających WSZYSTKIE wymienione komponenty.
    template <typename First, typename... Rest, typename Fn>
    void view(Fn&& fn) {
        auto* first = tryPool<First>();
        if (!first) return;
        first->each([&](std::uint32_t id, First& f) {
            if ((has<Rest>(Entity{id, 0}) && ...)) {
                fn(Entity{id, 0}, f, *tryPool<Rest>()->tryGet(id)...);
            }
        });
    }

    // Encje oznaczone do usunięcia w trakcie klatki — czyść na końcu.
    void queueDestroy(Entity e) { m_pendingDestroy.push_back(e); }
    void flushDestroyed();

    std::size_t aliveCount() const;

private:
    template <typename T>
    ComponentPool<T>& pool() {
        std::type_index ti(typeid(T));
        auto it = m_pools.find(ti);
        if (it == m_pools.end()) {
            auto p = std::make_unique<ComponentPool<T>>();
            auto* raw = p.get();
            m_pools.emplace(ti, std::move(p));
            return *raw;
        }
        return *static_cast<ComponentPool<T>*>(it->second.get());
    }

    template <typename T>
    ComponentPool<T>* tryPool() {
        auto it = m_pools.find(std::type_index(typeid(T)));
        if (it == m_pools.end()) return nullptr;
        return static_cast<ComponentPool<T>*>(it->second.get());
    }

    std::unordered_map<std::type_index,
                       std::unique_ptr<IComponentPool>> m_pools;
    std::vector<std::uint32_t> m_generations; // wersja per indeks
    std::vector<std::uint32_t> m_freeIds;     // do recyklingu
    std::uint32_t              m_next = 0;
    std::vector<Entity>        m_pendingDestroy;
};
