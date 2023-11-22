#include <cstring>

#include "CString.h"

using namespace std;

size_t CString::minStringSize(const CString &a, const CString &b)
{
    return (a.size < b.size ? a.size : b.size);
}

int CString::compare(const CString &a, const CString &b)
{
    return strncmp(a.data, b.data, minStringSize(a, b));
}

CString::CString(const char *string)
    : CContainer<char>(strlen(string), strlen(string) + 1)
{
    strncpy(this->data, string, this->capacity);
}

CString::CString(const CString &string) : CContainer<char>(string.size, string.capacity)
{
    memcpy(this->data, string.data, this->size + 1);
}

CString &CString::operator=(const CString &string)
{
    if (this != &string)
    {
        delete[] this->data;

        this->size = string.size;
        this->capacity = string.capacity;
        this->data = new char[this->capacity];

        memcpy(this->data, string.data, this->size + 1);
    }

    return *this;
}

bool CString::operator==(const CString &string) const
{
    return compare(*this, string) == 0;
}

bool CString::operator<(const CString &string) const
{
    return compare(*this, string) < 0;
}

ostream &operator<<(ostream &os, const CString &s)
{
    return os << s.data;
}
