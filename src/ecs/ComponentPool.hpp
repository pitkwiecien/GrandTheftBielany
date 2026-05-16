#pragma once
#include <cstdint>
#include <vector>
#include <cassert>
#include "Entity.hpp"

// Interfejs bazowy, by Registry trzymał pule różnych typów wspólnie.
class IComponentPool {
public:
    virtual ~IComponentPool() = default;
    virtual void remove(std::uint32_t entityId) = 0;
    virtual bool has(std::uint32_t entityId) const = 0;
};

// Sparse set: szybkie add/remove/lookup + zwarta tablica do iteracji.
// dense  : ciągła tablica komponentów (cache-friendly iteracja)
// sparse : entityId -> indeks w dense
template <typename T>
class ComponentPool : public IComponentPool {
public:
    template <typename... Args>
    T& emplace(std::uint32_t entityId, Args&&... args) {
        ensureSparse(entityId);
        if (m_sparse[entityId] != kInvalid) {
            return m_dense[m_sparse[entityId]]; // już istnieje
        }
        m_sparse[entityId] = static_cast<std::uint32_t>(m_dense.size());
        m_denseToEntity.push_back(entityId);
        m_dense.emplace_back(std::forward<Args>(args)...);
        return m_dense.back();
    }

    void remove(std::uint32_t entityId) override {
        if (!has(entityId)) return;
        std::uint32_t idx  = m_sparse[entityId];
        std::uint32_t last = static_cast<std::uint32_t>(m_dense.size() - 1);

        m_dense[idx]          = std::move(m_dense[last]);
        m_denseToEntity[idx]  = m_denseToEntity[last];
        m_sparse[m_denseToEntity[idx]] = idx;

        m_dense.pop_back();
        m_denseToEntity.pop_back();
        m_sparse[entityId] = kInvalid;
    }

    bool has(std::uint32_t entityId) const override {
        return entityId < m_sparse.size() && m_sparse[entityId] != kInvalid;
    }

    T* tryGet(std::uint32_t entityId) {
        if (!has(entityId)) return nullptr;
        return &m_dense[m_sparse[entityId]];
    }

    // Iteracja po wszystkich (entityId, komponent).
    template <typename Fn>
    void each(Fn&& fn) {
        for (std::size_t i = 0; i < m_dense.size(); ++i)
            fn(m_denseToEntity[i], m_dense[i]);
    }

    std::size_t size() const { return m_dense.size(); }

private:
    static constexpr std::uint32_t kInvalid = 0xFFFFFFFF;

    void ensureSparse(std::uint32_t entityId) {
        if (entityId >= m_sparse.size())
            m_sparse.resize(entityId + 1, kInvalid);
    }

    std::vector<T>             m_dense;
    std::vector<std::uint32_t> m_denseToEntity;
    std::vector<std::uint32_t> m_sparse;
};
