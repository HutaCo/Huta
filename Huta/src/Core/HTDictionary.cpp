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

#include <Core/HTDictionary.h>

NS_HT_BEGIN(Huta)

HTDictionary* HTDictionary::create()
{
    HTDictionary* object = new HTDictionary();
    if(object && object->init())
    {
        object->autorelease();
    } 
    else 
    {
        delete object;
    }
    return object;
}

HTDictionary* HTDictionary::createWithDictionary(HTDictionary* other)
{
    HTDictionary* object = HTDictionary::create();
    object->_map = other->_map;
    return object;
}

HTDictionary::HTDictionary()
{

}

HTDictionary::~HTDictionary() 
{

}

bool HTDictionary::init() 
{
    return true;
}

size_t HTDictionary::count()
{
    return _map.size();
}

HTArray* HTDictionary::allKeys()
{
    HTArray* array = HTArray::create();
    for(auto it: _map)
    {
        array->addObject(it.first.get());
    }
    return array;
}

HTArray* HTDictionary::allObjects()
{
    HTArray* array = HTArray::create();
    for(auto it: _map)
    {
        array->addObject(it.second.get());
    }
    return array;
}

HTRef* HTDictionary::objectForKey(HTRef* key)
{   
    HTRefPtr<HTRef> ref = _map[key];
    return ref.get();
}


void HTDictionary::setObject(HTRef* object, HTRef* key)
{
    if(object == nullptr || key == nullptr)
    {
        // TODO: throw exception if key or object is nullptr
    }

    _map[HTRefPtr<HTRef>(key)] = HTRefPtr<HTRef>(object);
}

void HTDictionary::removeObjectForKey(HTRef* key)
{
    _map.erase(key);
}

void HTDictionary::removeObjectsForKeys(HTArray* keys)
{

}

void HTDictionary::removeAllObjects()
{
    _map.clear();
}

HTDictionary* HTDictionary::clone() const
{
    HTDictionary* object = HTDictionary::create();
    object->_map = _map;
    return object;
}
NS_HT_END(Huta)