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

#include <Core/HTSet.h>

NS_HT_BEGIN(Huta)

HTSet::HTSet() 
{

}

HTSet::HTSet(const HTSet& other)
{
}

HTSet::~HTSet()
{
    removeAllObjects();
}

HTSet* HTSet::create()
{
    HTSet* ret = new HTSet();
    if(ret)
    {
        ret->autorelease();
    }
    return ret;
}

size_t HTSet::count() const
{
    return _set.size();
}

void HTSet::addObject(HTObject* object)
{
    if(_set.count(object) == 0)
    {
        _set.insert(object->retain());
    }
}

void HTSet::removeObject(HTObject* object)
{
    if(_set.erase(object) > 0)
    {
        object->release();
    }
}

void HTSet::removeAllObjects()
{
    for(auto it = _set.begin(); it != _set.end(); it++)
    {
        HTRef* obj = *it;
        _set.erase(it);
        obj->release();
    }
}

bool HTSet::containsObject(HTObject* object)
{
    return _set.find(object) != _set.end();
}

HTArray* HTSet::allObjects() const
{
    HTArray* array = HTArray::create();
    for(auto it = _set.begin(); it != _set.end(); it++)
    {
        array->addObject(*it);
    }
    return array;
}
NS_HT_END(Huta)