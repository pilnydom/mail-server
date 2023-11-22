#pragma once

#include "CContainer.h"

/**
 * @brief A dynamic array container class that inherits from CContainer<T>.
 *
 * @tparam T Type of elements stored in the array.
 */
template <typename T>
class CArray : public CContainer<T>
{
    /**
     * @brief Reallocates the data array to double its current capacity
     * and copies the existing elements to the new array.
     *
     */
    void realloc();

public:
    /**
     * @brief Constructs a new CArray object.
     *
     * @param size Initial size of the array.
     * @param capacity Initial capacity of the array.
     */
    CArray(size_t size = 0, size_t capacity = 10);

    /**
     * @brief Constructs a new CArray object by copying another CArray object.
     *
     * @param array Another CArray object to be copied.
     */
    CArray(const CArray &array);

    /**
     * @brief Assigns the contents of another CArray object to this object.
     *
     * @param array Another CArray object to be assigned.
     * @return CArray& Reference to this object.
     */
    CArray &operator=(const CArray &array);

    /**
     * @brief Inserts a value into a vector while sorting it and returns reference to that value.
     *
     * @param value Value to be inserted.
     * @return T& Reference to the inserted value.
     */
    T &insertSorted(const T &value);

    /**
     * @brief Inserts a value to the end of the vector.
     *
     * @param value Value to be inserted.
     */
    void pushBack(const T &value);

    /**
     * @brief Returns a reference to the element at the specified index.
     *
     * @param index Index of the element.
     * @return T& Reference to the element at the specified index.
     */
    T &operator[](size_t index) const;

    /**
     * @brief Searches for a value in the vector and returns a pair consisting of a boolean
     * indicating whether the value was found and a reference to the found value.
     *
     * @param value Value to be searched for.
     * @return std::pair<bool, T&> A pair consisting of a boolean indicating whether the value was found
     * and a reference to the found value.
     */
    std::pair<bool, T &> find(const T &value) const;
};
