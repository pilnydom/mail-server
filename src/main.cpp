#include <sstream>

#include "CMailServer.h"

using namespace std;

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
