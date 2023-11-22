#include "CArray.h"
#include "CMail.h"
#include "CMailServer.h"

using namespace std;

template<typename T>
void CArray<T>::realloc()
{
    this->capacity *= 2;
    T *newData = new T[this->capacity];

    for (size_t i = 0; i < this->size; ++i)
    {
        newData[i] = this->data[i];
    }

    delete[] this->data;
    this->data = newData;
}

template<typename T>
CArray<T>::CArray(size_t size, size_t capacity) : CContainer<T>(size, capacity) {}

template<typename T>
pair<bool, T &> CArray<T>::find(const T & value) const
{
    size_t low = 0;
    size_t high = this->size;

    while (low < high)
    {
        size_t mid = low + (high - low) / 2;

        if (this->data[mid] < value)
            low = mid + 1;
        else
            high = mid;
    }

    if (low < this->size && !(value < this->data[low]))
        return {true, this->data[low]};

    return {false, *this->data};
}

template<typename T>
T & CArray<T>::operator[](size_t index) const
{
    if (index >= this->size || index < 0)
        throw logic_error("Array: Out of reach");

    return this->data[index];
}

template<typename T>
void CArray<T>::pushBack(const T & value)
{
    if (this->capacity <= this->size)
        realloc();

    this->data[this->size++] = value;
}

template<typename T>
T & CArray<T>::insertSorted(const T & value)
{
    if (this->capacity <= this->size)
        realloc();

    size_t i = this->size;
    while (i > 0 && value < this->data[i - 1])
    {
        this->data[i] = this->data[i - 1];
        --i;
    }

    this->data[i] = value;
    ++this->size;
    return this->data[i];
}

template<typename T>
CArray<T> & CArray<T>::operator=(const CArray & array)
{
    if (this != &array)
    {
        delete[] this->data;

        this->size = array.size;
        this->capacity = array.capacity;
        this->data = new T[this->capacity];

        for (size_t i = 0; i < array.size; i++)
        {
            this->data[i] = array.data[i];
        }
    }

    return *this;
}

template<typename T>
CArray<T>::CArray(const CArray & array) : CContainer<T>(array.size, array.capacity)
{
    for (size_t i = 0; i < array.size; i++)
    {
        this->data[i] = array.data[i];
    }
}

template class CArray<CMail>;
template class CArray<CMailServer::TMailBox>;