# Mail Server

## About

The Mail Server is one of the individual homework assignments assigned for the course, which is aimed at practicing programming and algorithmization in the C++ language.

The assignment is to implement a `CMailServer` class that will simulate the operation of a simple mail server.

## Table of contents

- [Assignment description](#assignment)
- [Detailed specification](#detailed-specification)
    - [`CMail` class](#cmail-class)
    - [`CMailServer` class](#cmailserver-class)
    - [`CMailIterator` class](#cmailiterator-class)
- [Setup](#setup)
- [Example of use](#example-of-use)

## Assignment description

We assume that the server provides a means of sending e-mail within an organization. Each email is represented by an instance of the `CMail` class, and contains the sender's address, the recipient's address, and the message body (all strings). The mail server can send a message and can query the contents of sent and received mail (outbox and inbox) for individual email addresses. A list of sent and received mail is provided for each email address in the form of an iterator, the iterator instance provides methods to navigate through the mail list and access the contents of each mail. The `CMailServer` class itself must be able to handle copying correctly, its copies are used for archiving and auditing purposes.

> [!IMPORTANT]
> The assignment is aimed at practicing the understanding of shallow and deep copies of an object. For this reason, parts of the standard C++ libraries are suppressed in the task, in particular the STL and the C++ `std::string` data type. Only the C string library interface (`cstring`) is available. For implementation, it may be useful to create your own simple replacement for `std::string`.

## Detailed specification

### `CMail` class

The required `CMail` class has the following interface:

| Method/Operator | Expected Behavior |
| --------------- | ----------------- |
| constructor (`from`, `to`, `body`) | Creates an instance of an email with the `from`/`to`/`body` components filled in according to the parameters. It is assumed that email addresses are relatively short (tens to hundreds of characters) and that the message body can be relatively long (even a few megabytes). |
| `operator==` | Compares the contents of two instances of `CMail`, the method returns `true` if the instances are identical (all `from`, `to` and email contents match). |
| `operator<<` | Displays information about the mail in the specified stream. The format is obvious from the sample. |

### `CMailServer` class

The required `CMailServer` class has the following interface:

| Method/Operator | Expected Behavior |
| --------------- | ----------------- |
| default constructor | Creates an empty instance. |
| destructor | Releases the resources allocated by the instance. |
| copy constructor, `operator=` | Creates identical copies of the instance according to standard rules. |
| `sendMail(mail)` | Sends the email passed in the parameters, effectively placing it in the corresponding sender and recipient mailboxes. The email is always placed at the end of the existing list. There is no need to create a recipient or sender, the mailbox is automatically created after processing the first email containing the given email address. |
| `outbox(email)` | Accesses mail sent from the specified address. The return value is an instance of `CMailIterator` that allows you to browse emails sent from the `email` address. If an unknown email address is specified, the result is an iterator for an empty list of emails. The returned iterator must capture the state of the mailbox at the time it was created. That is, if the contents of the browsed mailbox change while the iterator is being used, that change will not be reflected in the values returned by the iterator. This behavior is demonstrated in the sample run for e.g. the `i5` iterator. |
| `inbox(email)` | Accesses mail received at the specified address. Otherwise, the method works the same as the `outbox` method. |

> [!IMPORTANT]
> The email addresses in the assignment can be arbitrary strings, and we match them case-sensitively - this is where the assignment differs from the real world, where email addresses have a prescribed formal form and where case is usually not distinguished.

### `CMailIterator` class

The required `CMailIterator` class has the following interface:

| Method/Operator | Expected Behavior |
| --------------- | ----------------- |
| `operator bool` | Determines whether the iterator refers to a valid email (returns `true`) or whether it has reached past the last email in the list (i.e. the email can no longer be read, returns `false`). |
| `operator!` | Works the same as the previous operator, but returns the opposite return value. |
| `operator*` | The \* operator will access the email at the current position. The return value is an instance of `CMail` (or a constant reference to `CMail`). There is no need to deal with the situation of accessing an email after the end of the list - the test environment always checks the validity of the iterator first and then accesses the referenced email if necessary. |
| `operator++` | The prefix operator ++ ensures that the iterator is moved to the next email in the list. Emails are iterated through in the order in which they were sent/received. Repeated calls to this iterator can move from the first email received/sent by the specified email address to the last (then the bool override operator must return `false`). |
| copy constructor, `operator=`, destructor | Depending on the implementation, the automatically generated variant may not be sufficient. The test environment does not explicitly copy iterators anywhere, but copying occurs when the return value is passed by the `inbox` and `outbox` methods. |

## Setup

1. Download this project as a ZIP and extract it
2. Open the folder with this project in the console
3. Compile and run it using the `make run` command

## Example of use

```cpp
#include <sstream>

#include "CMailServer.h"

int main()
{
    CMailServer mailServer;

    // Send some emails
    mailServer.sendMail(CMail("alice@example.com", "bob@example.com", "Hello Bob!"));
    mailServer.sendMail(CMail("bob@example.com", "alice@example.com", "Hi Alice!"));
    mailServer.sendMail(CMail("charlie@example.com", "bob@example.com", "Hey Bob, how's it going?"));

    // Print out the outbox for Alice
    CMailIterator aliceOutbox = mailServer.outbox("alice@example.com");
    while (aliceOutbox)
    {
        std::cout << *aliceOutbox << std::endl;
        ++aliceOutbox;
    }

    // Print out the inbox for Bob
    CMailIterator bobInbox = mailServer.inbox("bob@example.com");
    while (bobInbox)
    {
        std::cout << *bobInbox << std::endl;
        ++bobInbox;
    }

    return EXIT_SUCCESS;
}
```

```console
From: alice@example.com, To: bob@example.com, Body: Hello Bob!
From: alice@example.com, To: bob@example.com, Body: Hello Bob!
From: charlie@example.com, To: bob@example.com, Body: Hey Bob, how's it going?
```
