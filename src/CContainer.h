#pragma once

#include <iostream>

/**
 * @brief A generic container class that stores elements of type T.
 *
 * @tparam T The type of elements to be stored in the container.
 */
template <typename T>
class CContainer
{
protected:
    size_t size;
    size_t capacity;
    T *data;

public:
    /**
     * @brief Construct a new CContainer object.
     *
     * @param size The initial size of the container.
     * @param capacity The initial capacity of the container.
     */
    CContainer(size_t size = 0, size_t capacity = 10);

    /**
     * @brief Get the current size of the container.
     *
     * @return size_t The current size of the container.
     */
    size_t getSize() const;

    /**
     * @brief Destroy the CContainer object.
     *
     */
    virtual ~CContainer();
};