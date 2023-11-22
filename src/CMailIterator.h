#pragma once

#include "CMail.h"
#include "CArray.h"

/**
 * @brief Iterator class for iterating over a collection of CMail objects.
 *
 */
class CMailIterator
{
    CArray<CMail> mails;
    size_t index;

public:
    /**
     * @brief Construct a new CMailIterator object
     *
     * @param mails Collection of CMail objects to iterate over.
     * @param index Starting index of the iterator.
     */
    CMailIterator(const CArray<CMail> &mails = CArray<CMail>(), size_t index = 0);

    /**
     * @brief Copy constructor for CMailIterator.
     *
     * @param mailIterator CMailIterator object to copy.
     */
    CMailIterator(const CMailIterator &mailIterator);

    /**
     * @brief Copy assignment operator for CMailIterator.
     *
     * @param mailIterator CMailIterator object to copy.
     * @return CMailIterator& Reference to the current object.
     */
    CMailIterator &operator=(const CMailIterator &mailIterator);

    /**
     * @brief Default destructor for CMailIterator.
     *
     */
    ~CMailIterator() = default;

    /**
     * @brief Conversion operator to bool.
     *
     * @return true If the iterator is valid.
     * @return false If the iterator is invalid.
     */
    explicit operator bool() const;

    /**
     * @brief Logical NOT operator.
     *
     * @return true If the iterator is invalid.
     * @return false If the iterator is valid.
     */
    bool operator!() const;

    /**
     * @brief Dereference operator.
     *
     * @return const CMail& Reference to the current CMail object.
     */
    const CMail &operator*() const;

    /**
     * @brief Prefix increment operator.
     *
     * @return CMailIterator& Reference to the current object.
     */
    CMailIterator &operator++();
};
