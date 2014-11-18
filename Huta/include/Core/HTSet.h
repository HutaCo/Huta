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

#include <Core/HTMacros.h>
#include <Core/HTObject.h>
#include <Core/HTArray.h>

#include <set>


NS_HT_BEGIN(Huta)

class HTSet: public HTObject
{
public:
    HTSet();
    HTSet(const HTSet& other);
    ~HTSet();

    // Create an empty set
    static HTSet* create();

    // Return element count of the set
    size_t count() const;

    // Add a certain object
    void addObject(HTObject* object);

    // Remove a certain object
    void removeObject(HTObject* object);

    // Remove all objects
    void removeAllObjects();

    // Return a bool value that indicates whether object is present in set
    bool containsObject(HTObject* object);

    // Return all objects of set
    HTArray* allObjects() const;
private:
    std::set<HTRef*> _set;
};

NS_HT_END(Huta)