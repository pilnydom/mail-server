#include "CMailIterator.h"

CMailIterator::CMailIterator(const CArray<CMail> &mails, size_t index)
    : mails(mails), index(index) {}

CMailIterator::CMailIterator(const CMailIterator &mailIterator)
    : mails(mailIterator.mails), index(mailIterator.index) {}

CMailIterator &CMailIterator::operator=(const CMailIterator &mailIterator)
{
    if (this != &mailIterator)
    {
        mails = mailIterator.mails;
        index = mailIterator.index;
    }

    return *this;
}

CMailIterator::operator bool() const
{
    return index < mails.getSize();
}

bool CMailIterator::operator!() const
{
    return !bool(*this);
}

const CMail &CMailIterator::operator*() const
{
    return mails[index];
}

CMailIterator &CMailIterator::operator++()
{
    ++index;
    return *this;
}
