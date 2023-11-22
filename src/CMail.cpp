#include "CMail.h"

using namespace std;

CMail::CMail(const char *from, const char *to, const char *body)
    : from(from), to(to), body(body) {}

CMail::CMail(const CMail &mail) : from(mail.from), to(mail.to), body(mail.body) {}

CMail &CMail::operator=(const CMail &mail)
{
    if (this != &mail)
    {
        from = mail.from;
        to = mail.to;
        body = mail.body;
    }

    return *this;
}

bool CMail::operator==(const CMail &mail) const
{
    return from == mail.from && to == mail.to && body == mail.body;
}

bool CMail::operator<(const CMail &mail) const
{
    if (from < mail.from)
        return true;

    if (mail.from < from)
        return false;

    if (to < mail.to)
        return true;

    if (mail.to < to)
        return false;

    return body < mail.body;
}

CString CMail::sender() const
{
    return from;
}

CString CMail::receiver() const
{
    return to;
}

ostream &operator<<(ostream &os, const CMail &mail)
{
    return os << "From: " << mail.from << ", To: " << mail.to << ", Body: " << mail.body;
}
