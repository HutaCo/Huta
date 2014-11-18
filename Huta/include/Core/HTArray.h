// The MIT License (MIT)
//
// Copyright (c) 2014 Trung Tran <trungtran0689@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <Core/HTObject.h>
#include <Core/HTMacros.h>

#include <vector>
#include <algorithm>

NS_HT_BEGIN(Huta)

class HTArray: public HTObject, public HTClonable
{
public:

    typedef std::vector<HTRefPtr<HTRef>>::iterator iterator;
    typedef std::vector<HTRefPtr<HTRef>>::const_iterator const_iterator;

    // Create an empty array. Default capacity is 10
    static HTArray* create();

    // Creates an array with objects. End with NULL
    static HTArray* create(HTRef* object, ...) HT_REQUIRES_NULL_TERMINATION;

    // Create an array with an object
    static HTArray* createWithObject(HTRef* object);

    // Create an array with default capacity
    static HTArray* createWithCapacity(size_t capacity);

    // Create an array from an existing array
    static HTArray* createWithArray(HTArray* other);

    // Initializes an array
    bool init();

    // Initialize an array with an object
    bool initWithObject(HTRef* object);

    // Initialize an array with some objects
    bool initWithObjects(HTRef* object, ...) HT_REQUIRES_NULL_TERMINATION;

    // Initialize an array with capacity
    bool initWithCapacity(size_t capacity);

    // Initialize an array with an existing array
    bool initWithArray(HTArray* other);


    virtual HTArray* clone() const;

    HTArray();
    ~HTArray();

    // Return element count of the array
    size_t count() const 
    {
        return _data.size();
    }

    // Return capacity of the array
    size_t capacity() const 
    {
        return _data.capacity();
    }

    // Retun index of a certain object return UINT_MAX if doesn't contain the object
    ssize_t getIndexOfObject(HTRef* object) const;

    // Return an element with a certain index
    HTRef* getObjectAtIndex(size_t index);

    // Return the last element of the array
    HTRef* getLastObject();

    // Return a bool value that indicates whether object is present in array
    bool containsObject(HTRef* object) const;

    // Compare with another array
    bool isEqualToArray(HTArray* other);

    // Add a certain object
    void addObject(HTRef* object);

    // Add all elements of an existing array
    void addObjectsFromArray(HTArray* other);

    // Insert a certain object at a certain index
    void insertObject(HTRef* object, size_t index);

    // Set a certain object a a certain index
    void setObject(HTRef* object, size_t index);

    // Remove a certain object 
    void removeObject(HTRef* object);

    // Remove object at a certain index
    void removeObjectAtIndex(size_t index);

    // Remove last object
    void removeLastObject();

    // Swap two objects
    void swap(ssize_t indexOne, ssize_t indexTwo)
    {
        std::swap(_data[indexOne], _data[indexTwo]);
    }


    iterator begin() { return _data.begin(); }

    iterator end() {return _data.end(); }

private:
    std::vector< HTRefPtr<HTRef> > _data;
};

NS_HT_END(Huta)