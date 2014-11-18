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

#include <Core/HTArray.h>

NS_HT_BEGIN(Huta)
HTArray::HTArray()
{
    init();
}

HTArray::~HTArray()
{
    
}

HTArray* HTArray::create() 
{
    HTArray* array = new HTArray();
    if(array && array->initWithCapacity(10))
    {
        array->autorelease();
    } 
    else 
    {
        HT_SAFE_DELETE(array);
    }

    return array;
}

HTArray* HTArray::createWithObject(HTRef* object)
{
    HTArray* array = new HTArray();
    if(array && array->initWithObject(object))
    {
        array->autorelease();
    }
    else 
    {
        HT_SAFE_DELETE(array);
    }
    return array;
}


HTArray* HTArray::create(HTRef* object, ...)
{
    va_list args;
    va_start(args, object);

    HTArray* array = create();
    if(array && object)
    {
        array->addObject(object);
        HTRef* obj = va_arg(args, HTRef*);
        while(obj) 
        {
            array->addObject(obj);
            obj = va_arg(args, HTRef*);
        }
    } 
    else 
    {
        HT_SAFE_DELETE(array);
    }

    va_end(args);
    return array;
}

HTArray* HTArray::createWithArray(HTArray* other)
{
    return other->clone();
}

HTArray* HTArray::createWithCapacity(size_t capacity)
{
    HTArray* array = new HTArray();
    if(array && array->initWithCapacity(capacity)) 
    {
        array->autorelease();
    } 
    else
    {
        HT_SAFE_DELETE(array);
    }
    return array;
}

bool HTArray::init()
{
    return initWithCapacity(10);
}

bool HTArray::initWithObject(HTRef* object)
{
    bool ret = initWithCapacity(10);
    if(ret)
    {
        addObject(object);
    }
    return ret;
}

bool HTArray::initWithObjects(HTRef* object, ...)
{
    bool ret = false;
    
    va_list args;
    va_start(args, object);

    if(object)
    {
        addObject(object);
        HTRef* obj = va_arg(args, HTRef*);
        while(obj)
        {
            addObject(obj);
            obj = va_arg(args, HTRef*);
        }
        ret = true;
    }   

    va_end(args);
    return ret;
}

bool HTArray::initWithCapacity(size_t capacity)
{
    _data.reserve(capacity);
    return true;
}

bool HTArray::initWithArray(HTArray* other)
{
    _data = other->_data;
    return true;
}

ssize_t HTArray::getIndexOfObject(HTRef* object) const
{
    auto it = _data.begin();
    for(size_t index = 0; it != _data.end(); ++it, ++index)
    {
        if(it->get() == object)
        {
            return index;
        }
    }

    return -1;
}

HTRef* HTArray::getObjectAtIndex(size_t index) 
{
    return _data[index].get();
}

HTRef* HTArray::getLastObject()
{
    return _data.back().get();
}

bool HTArray::containsObject(HTRef* object) const
{
    ssize_t index = getIndexOfObject(object);
    return (index >= 0);
}

bool HTArray::isEqualToArray(HTArray* other)
{
    if(other->count() != count()) return false;

    for(size_t index = 0; index < count(); ++index)
    {
        if(getObjectAtIndex(index) != other->getObjectAtIndex(index)) {
            return false;
        }
    }
    return true;
}

void HTArray::addObject(HTRef* object)
{
    _data.push_back(HTRefPtr<HTRef>(object));
}

void HTArray::addObjectsFromArray(HTArray* other)
{
    _data.insert(_data.end(), other->_data.begin(), other->_data.end());
}

void HTArray::insertObject(HTRef* object, size_t index)
{
    _data.insert(std::begin(_data) + index, HTRefPtr<HTRef>(object));
}

void HTArray::setObject(HTRef* object, size_t index)
{
    _data[index] = HTRefPtr<HTRef>(object);
}

void HTArray::removeObject(HTRef* object)
{
    _data.erase(std::remove(_data.begin(), _data.end(), object));
}

void HTArray::removeObjectAtIndex(size_t index)
{
    auto obj = _data[index];
    _data.erase(_data.begin() + index);
}

void HTArray::removeLastObject() 
{
    _data.pop_back();
}

HTArray* HTArray::clone() const
{
    HTArray* ret = new HTArray();
    ret->autorelease();
    ret->initWithCapacity(this->_data.size() > 0 ? this->_data.size() : 1);

    HTRef* obj = nullptr;
    HTRef* tmpObj = nullptr;
    HTClonable *clonable = nullptr;
    auto it = _data.begin();
    for(;it != _data.end(); ++it)
    {
        obj = it->get();
        clonable = dynamic_cast<HTClonable*>(obj);
        if(clonable)
        {
            tmpObj = dynamic_cast<HTRef*>(clonable->clone());
            if(tmpObj)
            {
                ret->addObject(tmpObj);
            }
        }
    }
    return ret;
}

NS_HT_END(Huta)