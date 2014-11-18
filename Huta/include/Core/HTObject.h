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
#include <Core/HTRef.h>

NS_HT_BEGIN(Huta)

class HTString;

class HTClonable {
public:
    virtual HTClonable* clone() const = 0;
    virtual ~HTClonable() {};
};


class HTNonCloneable {
public:
    HTNonCloneable() {}
    HTNonCloneable(const HTNonCloneable&) = delete;
    HTNonCloneable &operator=(const HTNonCloneable&) = delete; 
};


class HTObject: public HTRef
{
public:

    // Increase reference count by one 
    HTObject* retain() override;

    // Decrease reference count by one
    // Release object if reference count is 0
    void release() override;

    // Put object to autorelease pool
    HTObject* autorelease() override;

    // Get reference count
    unsigned int getReferenceCount() const override;

    // Compare two objects
    virtual bool isEqual(const HTObject* object);

    // Object description
    virtual HTString* toString() const;
public:
    HTObject();
protected:
    virtual ~HTObject();
#ifdef HT_MEM_LEAK_TRACK
    static void printLeaks();
#endif

protected:
    unsigned int _referenceCount;
    friend class HTAutoreleasePool;
};

NS_HT_END(Huta)
