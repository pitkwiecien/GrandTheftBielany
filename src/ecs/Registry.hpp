#pragma once
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
        void queueDestroy(Entity e) { pendingDestroy.push_back(e); }
        void flushDestroyed();

        template <typename T>
        T& add(Entity e) {
            return pool<T>().emplace(e.id);
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

        template <typename First, typename... Rest, typename F>
        void view(F&& fn) {
            auto* first = tryPool<First>();
            if (!first) return;
            first->each([&](unsigned int id, First& f) {
                if ((has<Rest>(Entity{id}) && ...))
                    fn(Entity{id}, f, *tryPool<Rest>()->tryGet(id)...);
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
        std::vector<unsigned int> freeIds;
        unsigned int next = 0;
        std::vector<Entity> pendingDestroy;
};
