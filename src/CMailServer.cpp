#include "CMailServer.h"

using namespace std;

CMailServer::TMailBox::TMailBox(const CString &email) : email(email) {}

CMailServer::TMailBox::TMailBox(const CMailServer::TMailBox &mailbox)
    : email(mailbox.email), inbox(mailbox.inbox), outbox(mailbox.outbox) {}

CMailServer::TMailBox &CMailServer::TMailBox::operator=(const CMailServer::TMailBox &mailbox)
{
    if (this != &mailbox)
    {
        email = mailbox.email;
        inbox = mailbox.inbox;
        outbox = mailbox.outbox;
    }

    return *this;
}

bool CMailServer::TMailBox::operator<(const CMailServer::TMailBox &mailbox) const
{
    return email < mailbox.email;
}

void CMailServer::TMailBox::send(const CMail &mail)
{
    outbox.pushBack(mail);
}

void CMailServer::TMailBox::recieve(const CMail &mail)
{
    inbox.pushBack(mail);
}

CMailServer::TMailBox &CMailServer::createMailbox(const CString &email)
{
    return mailboxes.insertSorted(TMailBox(email));
}

pair<bool, CMailServer::TMailBox &> CMailServer::findMailbox(const CString &email) const
{
    return mailboxes.find(email);
}

CMailIterator CMailServer::createIterator(const char *email, bool outbox) const
{
    CMailIterator mailIterator;

    auto [found, mailbox] = findMailbox(email);
    if (found)
    {
        mailIterator = outbox ? mailbox.outbox : mailbox.inbox;
    }

    return mailIterator;
}

void CMailServer::processMail(const CString &email, const CMail &mail, void (CMailServer::TMailBox::*action)(const CMail &))
{
    auto [found, mailbox] = findMailbox(email);
    if (!found)
        (createMailbox(email).*action)(mail);
    else
        (mailbox.*action)(mail);
}

CMailServer::CMailServer(const CMailServer &mailserver)
    : mailboxes(mailserver.mailboxes) {}

CMailServer &CMailServer::operator=(const CMailServer &mailserver)
{
    if (this != &mailserver)
        mailboxes = mailserver.mailboxes;

    return *this;
}

void CMailServer::sendMail(const CMail &mail)
{
    processMail(mail.sender(), mail, &TMailBox::send);
    processMail(mail.receiver(), mail, &TMailBox::recieve);
}

CMailIterator CMailServer::outbox(const char *email) const
{
    return createIterator(email, true);
}

CMailIterator CMailServer::inbox(const char *email) const
{
    return createIterator(email, false);
}
