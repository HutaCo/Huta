// The MIT License (MIT)
//
// Copyright (c) 2014 Trung Tran
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
#include <Core/HTRef.h>
#include <Core/HTMacros.h>
#include <iostream>
#include <vector>

NS_HT_BEGIN(Huta)

class HTAutoreleasePool {
public:
    HTAutoreleasePool();
    HTAutoreleasePool(const std::string &name);

    ~HTAutoreleasePool();

    void addObject(HTRef *object);
    void clear();
    
    bool isClearing() const { return _isClearing; }

    bool contains(HTRef *object) const;

    static HTAutoreleasePool *getCurrentPool();

private:
    std::vector<HTRef*> _managedObjectArray;
    std::string _name;
    bool _isClearing;
};

class HTPoolManager {
public:
    static HTPoolManager* getInstance();

    HTAutoreleasePool *getCurrentPool() const;

    bool isObjectInPools(HTRef *obj) const;

    friend class HTAutoreleasePool;

private: 
    HTPoolManager();
    ~HTPoolManager();

    void push(HTAutoreleasePool *pool);
    void pop();

    static HTPoolManager *s_singleInstance;
    std::vector<HTAutoreleasePool*> _releasePoolStack;

};

#define autoreleasepool for(HTAutoreleasePool pool; !pool.isClearing(); pool.clear())
NS_HT_END(Huta)