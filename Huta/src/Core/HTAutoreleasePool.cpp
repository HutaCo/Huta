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

#include <Core/HTAutoreleasePool.h>

NS_HT_BEGIN(Huta)

HTAutoreleasePool::HTAutoreleasePool()
: _name("")
, _isClearing(false)
{
    _managedObjectArray.reserve(150);
    HTPoolManager::getInstance()->push(this);
}

HTAutoreleasePool::HTAutoreleasePool(const std::string &name)
: _name(name)
, _isClearing(false) 
{
    _managedObjectArray.reserve(150);
    HTPoolManager::getInstance()->push(this);
}

HTAutoreleasePool::~HTAutoreleasePool() 
{
    clear();

    HTPoolManager::getInstance()->pop();
}

void HTAutoreleasePool::addObject(HTRef* object) 
{
    _managedObjectArray.push_back(object);
}

void HTAutoreleasePool::clear() 
{
    _isClearing = true;

    for(const auto obj : _managedObjectArray) 
    {
        obj->release();
    }
    _managedObjectArray.clear();
}

bool HTAutoreleasePool::contains(HTRef* object) const 
{
    for(const auto &obj : _managedObjectArray)
    {
        if(obj == object)
        return true;
    }
    return false;
}

HTAutoreleasePool *HTAutoreleasePool::getCurrentPool() 
{
    return HTPoolManager::getInstance()->getCurrentPool();
}

//--------------------------------------------------------------------
//
// PoolManager
//
//--------------------------------------------------------------------


HTPoolManager* HTPoolManager::s_singleInstance = nullptr;

HTPoolManager* HTPoolManager::getInstance()
{
    if (s_singleInstance == nullptr)
    {
        s_singleInstance = new (std::nothrow) HTPoolManager();
        // Add the first auto release pool
        new HTAutoreleasePool("Huta autorelease pool");
    }
    return s_singleInstance;
}

HTPoolManager::HTPoolManager()
{
    _releasePoolStack.reserve(10);
}

HTPoolManager::~HTPoolManager()
{
    
    while (!_releasePoolStack.empty())
    {
        HTAutoreleasePool* pool = _releasePoolStack.back();
        
        delete pool;
    }
}

HTAutoreleasePool* HTPoolManager::getCurrentPool() const
{
    return _releasePoolStack.back();
}

bool HTPoolManager::isObjectInPools(HTRef* obj) const
{
    for (const auto& pool : _releasePoolStack)
    {
        if (pool->contains(obj))
            return true;
    }
    return false;
}

void HTPoolManager::push(HTAutoreleasePool *pool)
{
    _releasePoolStack.push_back(pool);
}

void HTPoolManager::pop()
{
    // TODO: throw exception
    _releasePoolStack.pop_back();
}


NS_HT_END(Huta)