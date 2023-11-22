#pragma once

#include "CContainer.h"

/**
 * @brief A class representing a C-style string with additional functionality.
 */
class CString : public CContainer<char>
{
    /**
     * @brief Returns the minimum size of two strings.
     * @param a The first string to compare.
     * @param b The second string to compare.
     * @return The minimum size of the two strings.
     */
    static size_t minStringSize(const CString &a, const CString &b);

    /**
     * @brief Compares two strings lexicographically and returns an integer indicating their relative order.
     * @param a The first string to compare.
     * @param b The second string to compare.
     * @return An integer indicating the relative order of the two strings.
     *         If a < b, returns a negative value.
     *         If a > b, returns a positive value.
     *         If a == b, returns 0.
     */
    static int compare(const CString &a, const CString &b);

public:
    /**
     * @brief Constructs a CString object from a C-style string.
     * @param string The C-style string to construct the object from.
     */
    CString(const char *string = "");

    /**
     * @brief Copy constructor.
     * @param string The CString object to copy.
     */
    CString(const CString &string);

    /**
     * @brief Copy assignment operator.
     * @param string The CString object to copy.
     * @return A reference to the assigned CString object.
     */
    CString &operator=(const CString &string);

    /**
     * @brief Equality comparison operator.
     * @param string The CString object to compare to.
     * @return true if the two CString objects are equal, false otherwise.
     */
    bool operator==(const CString &string) const;

    /**
     * @brief Less-than comparison operator.
     * @param string The CString object to compare to.
     * @return true if this CString object is less than the other, false otherwise.
     */
    bool operator<(const CString &string) const;

    /**
     * @brief Output stream operator.
     * @param os The output stream to write to.
     * @param s The CString object to write to the output stream.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const CString &s);
};
