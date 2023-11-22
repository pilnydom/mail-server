#include "CContainer.h"
#include "CMail.h"
#include "CMailServer.h"

template <typename T>
CContainer<T>::CContainer(size_t size, size_t capacity)
    : size(size), capacity(capacity), data(new T[capacity]) {}

template <typename T>
size_t CContainer<T>::getSize() const
{
    return this->size;
}

template <typename T>
CContainer<T>::~CContainer()
{
    delete[] data;
}

template class CContainer<char>;
template class CContainer<CMail>;
template class CContainer<CMailServer::TMailBox>;