#pragma once

#include "CString.h"
#include "CMail.h"
#include "CMailIterator.h"

/**
 * @brief Represents a mail server that manages mailboxes and allows sending and receiving emails.
 */
class CMailServer
{
    /**
     * @brief Represents a mailbox for a specific email address, containing an inbox and an outbox.
     */
    struct TMailBox
    {
        /**
         * @brief The email address associated with this mailbox.
         */
        CString email;

        /**
         * @brief An array of CMail objects representing the emails in the inbox.
         */
        CArray<CMail> inbox;

        /**
         * @brief An array of CMail objects representing the emails in the outbox.
         */
        CArray<CMail> outbox;

        /**
         * @brief Default constructor.
         */
        TMailBox() = default;

        /**
         * @brief Constructor that sets the email address of the mailbox.
         * @param email The email address to associate with this mailbox.
         */
        TMailBox(const CString &email);

        /**
         * @brief Copy constructor.
         * @param mailbox The mailbox to copy.
         */
        TMailBox(const TMailBox &mailbox);

        /**
         * @brief Copy assignment operator.
         * @param mailbox The mailbox to copy.
         * @return A reference to this mailbox.
         */
        TMailBox &operator=(const TMailBox &mailbox);

        /**
         * @brief Destructor.
         */
        ~TMailBox() = default;

        /**
         * @brief Less-than comparison operator.
         * @param mailbox The mailbox to compare to.
         * @return True if this mailbox is less than the other mailbox, false otherwise.
         */
        bool operator<(const TMailBox &mailbox) const;

        /**
         * @brief Adds a mail to the outbox.
         * @param mail The mail to add to the outbox.
         */
        void send(const CMail &mail);

        /**
         * @brief Adds a mail to the inbox.
         * @param mail The mail to add to the inbox.
         */
        void recieve(const CMail &mail);
    };

    /**
     * @brief A container to hold all the mailboxes.
     */
    CArray<TMailBox> mailboxes;

    /**
     * @brief Creates a new mailbox with the given email address and inserts it into the mailboxes array in a sorted manner.
     *
     * @param email The email address for the new mailbox.
     * @return A reference to the newly created mailbox.
     */
    TMailBox &createMailbox(const CString &email);

    /**
     * @brief Finds a mailbox with the given email address in the mailboxes array.
     *
     * @param email The email address to find the associated mailbox.
     * @return A pair containing a boolean indicating whether the mailbox was found and a reference to the mailbox.
     */
    std::pair<bool, TMailBox &> findMailbox(const CString &email) const;

    /**
     * @brief Returns an iterator to the outbox or inbox of the mailbox associated with the given email address if found.
     *
     * @param email The email address to find the associated mailbox.
     * @param outbox A boolean indicating whether to return an iterator to the outbox (true) or inbox (false).
     * @return An iterator to the outbox or inbox of the found mailbox.
     */
    CMailIterator createIterator(const char *email, bool outbox) const;

    /**
     * @brief Finds or creates a mailbox with the given email address and calls the given action (send or receive) on it with the given mail.
     *
     * @param email The email address to find or create the associated mailbox.
     * @param mail The mail to process.
     * @param action The action to perform on the mailbox (send or receive).
     */
    void processMail(const CString &email, const CMail &mail, void (TMailBox::*action)(const CMail &));

public:
    /**
     * @brief Default constructor.
     */
    CMailServer(void) = default;

    /**
     * @brief Copy constructor.
     *
     * @param mailserver The CMailServer object to copy.
     */
    CMailServer(const CMailServer &mailserver);

    /**
     * @brief Copy assignment operator.
     *
     * @param mailserver The CMailServer object to copy.
     * @return A reference to the copied CMailServer object.
     */
    CMailServer &operator=(const CMailServer &mailserver);

    /**
     * @brief Default destructor.
     */
    ~CMailServer(void) = default;

    /**
     * @brief Sends an email.
     *
     * Finds or creates the sender and receiver mailboxes and calls their send and receive methods respectively.
     *
     * @param mail The email to send.
     */
    void sendMail(const CMail &mail);

    /**
     * @brief Returns an iterator to the outbox of the mailbox associated with the given email address.
     *
     * @param email The email address to find the associated mailbox.
     * @return An iterator to the outbox of the found mailbox.
     */
    CMailIterator outbox(const char *email) const;

    /**
     * @brief Returns an iterator to the inbox of the mailbox associated with the given email address.
     *
     * @param email The email address to find the associated mailbox.
     * @return An iterator to the inbox of the found mailbox.
     */
    CMailIterator inbox(const char *email) const;
};
