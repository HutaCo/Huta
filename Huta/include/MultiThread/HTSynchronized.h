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
#include <mutex>
#include <condition_variable>

NS_HT_BEGIN(Huta)

class HTMutex
{
public:
    void lock()
    {
        _mutex.lock();
    }

    void unlock()
    {
        _mutex.unlock();
    }

    friend class HTCondition;
private:
    std::mutex _mutex;
};

class HTLock
{
public:
    HTLock(HTMutex &mutex):_mutex(mutex), _locked(false) 
    {
        _mutex.lock();
    }

    ~HTLock() 
    {
        _mutex.unlock();
    }

    operator bool () const 
    {
        return _locked;
    }

    void setUnlock() 
    {
        _locked = false;
    }
private:
    HTMutex &_mutex;
    bool _locked;
};


class HTCondition
{
public:
    HTCondition(HTMutex &mutex):_mutex(mutex){}
    void wait(std::function<bool()> ready) 
    {
        std::unique_lock<std::mutex> lock(_mutex._mutex);
        _condition.wait(lock, ready);
    }
    void notify() 
    {
        _condition.notify_one();
    }
    void notifyAll() 
    {
        _condition.notify_all();
    }
private:
    std::condition_variable _condition;
    HTMutex &_mutex;
};


class HTSemanphore 
{
public:
private:
};


// synchronized(mutex) { }
#define synchronized(M) for(HTLock myLock(M); myLock; myLock.setUnlock())

NS_HT_END(Huta)