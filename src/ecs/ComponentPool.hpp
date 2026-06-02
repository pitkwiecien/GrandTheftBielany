#pragma once
#include <unordered_map>

// interfejs bazowy, umozliwa registry trzymanie puli różnych typów wspólnie.
class IComponentPool {
    public:
        virtual ~IComponentPool() =default;
        virtual void remove(unsigned int entityId) =0;
};

template <typename T>
class ComponentPool : public IComponentPool {
    public:
        T& emplace(unsigned int entityId) {
            // zwraca iterator do istniejacego wpisu
            return m_data.try_emplace(entityId).first->second;
        }

        void remove(unsigned int entityId) override {
            m_data.erase(entityId);
        }

        bool has(unsigned int entityId) const {
            return m_data.count(entityId) != 0;
        }

        T* tryGet(unsigned int entityId) {
            auto it = m_data.find(entityId);
            return it != m_data.end() ? &it->second : nullptr;
        }

        // iteracja po wszystkich (entityId, komponent).
        template <typename F>
        void each(F&& f) {
            for (auto& [id, comp] : m_data) f(id, comp);
        }

    private:
        std::unordered_map<unsigned int, T> m_data;
};
