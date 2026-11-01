#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

template <typename T>
class Vector 
{
private:
    T* data;        
    int capacity;   
    int length;     

    void reallocate(int newCapacity) 
    {
        T* newData = new T[newCapacity];
        for (int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
   
    Vector(int initCapacity = 4) : capacity(initCapacity), length(0) 
    {
        if (capacity < 1) capacity = 4;
        data = new T[capacity];
    }

    Vector(const Vector& other) : capacity(other.capacity), length(other.length) 
    {
        data = new T[capacity];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }


    Vector& operator=(const Vector& other) 
    {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            length = other.length;
            data = new T[capacity];
            for (int i = 0; i < length; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Vector() 
    {
        delete[] data;
    }

    void push_back(const T& val) 
    {
        if (length >= capacity) {
            reallocate(capacity * 2); 
        }
        data[length++] = val;
    }

    void erase(int index) 
    {
        if (index < 0 || index >= length) return;
        for (int i = index; i < length - 1; i++) {
            data[i] = data[i + 1];
        }
        length--;
    }

    void erase(T* it) 
    {
        int index = it - data;
        erase(index);
    }

    void clear() { length = 0; }

    int size() const { return length; }

    bool empty() const { return length == 0; }

    T& operator[](int index) { return data[index]; }

    const T& operator[](int index) const { return data[index]; }

    T* begin() { return data; }
    const T* begin() const { return data; }
    T* end() { return data + length; }
    const T* end() const { return data + length; }
};

#endif