#pragma once

#include "CString.h"

/**
 * @brief Represents an email message with sender, receiver and body.
 */
class CMail
{
    CString from;
    CString to;
    CString body;

public:
    /**
     * @brief Default constructor for CMail.
     */
    CMail() = default;

    /**
     * @brief Constructor for CMail.
     * @param from The email address of the sender.
     * @param to The email address of the receiver.
     * @param body The body of the email message.
     */
    CMail(const char *from, const char *to, const char *body);

    /**
     * @brief Copy constructor for CMail.
     * @param mail The CMail object to be copied.
     */
    CMail(const CMail &mail);

    /**
     * @brief Assignment operator for CMail.
     * @param mail The CMail object to be assigned.
     * @return A reference to the assigned CMail object.
     */
    CMail &operator=(const CMail &mail);

    /**
     * @brief Default destructor for CMail.
     */
    ~CMail() = default;

    /**
     * @brief Equality operator for CMail.
     * @param mail The CMail object to be compared.
     * @return True if the two CMail objects are equal, false otherwise.
     */
    bool operator==(const CMail &mail) const;

    /**
     * @brief Less than operator for CMail.
     * @param mail The CMail object to be compared.
     * @return True if this CMail object is less than the other, false otherwise.
     */
    bool operator<(const CMail &mail) const;

    /**
     * @brief Returns the email address of the sender.
     * @return The email address of the sender.
     */
    CString sender() const;

    /**
     * @brief Returns the email address of the receiver.
     * @return The email address of the receiver.
     */
    CString receiver() const;

    /**
     * @brief Overloaded stream insertion operator for CMail.
     * @param os The output stream.
     * @param mail The CMail object to be inserted into the output stream.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const CMail &mail);
};
