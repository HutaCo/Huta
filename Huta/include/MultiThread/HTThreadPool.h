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

#include <deque>
#include <MultiThread/HTThread.h>
#include <MultiThread/HTSynchronized.h>

NS_HT_BEGIN(Huta) 

class HTThreadPool;
  
// our worker thread objects
class HTWorker {
public:
    HTWorker(HTThreadPool &s) : pool(s) { }
    void operator()();
private:
    HTThreadPool &pool;
};
  
// the actual thread pool
class HTThreadPool : public HTObject{
public:
    HTThreadPool(size_t);
    template<class F>
    void enqueue(F f);
    ~HTThreadPool();
    friend class HTWorker;
private:
    // need to keep track of threads so we can join them
    std::vector< HTRefPtr<HTThread> > workers;
 
    // the task queue
    std::deque< std::function<void()> > tasks;
 
    // synchronization
    HTMutex queueMutex;
    HTCondition condition;
    bool stop;
};


void HTWorker::operator()()
{
    std::function<void()> task;
    while(true)
    {
        synchronized(pool.queueMutex) 
        {    
            pool.condition.wait([&]{ return !pool.stop && pool.tasks.empty(); });
            if(pool.stop) // exit if the pool is stopped
                return;
 
            // get the task from the queue
            task = pool.tasks.front();
            pool.tasks.pop_front();
        }   
        task();
    }
}


// the constructor just launches some amount of workers
HTThreadPool::HTThreadPool(size_t threads)
    :  condition(queueMutex), stop(false)
{
    for(size_t i = 0; i<threads; ++i)
    {
        HTThread *thread = new HTThread(HTWorker(*this));
        HTRefPtr<HTThread> ref(thread);
        workers.push_back(ref);
        thread->release();
    }
}
   
// the destructor joins all threads
HTThreadPool::~HTThreadPool()
{
    // stop all threads
    stop = true;
    condition.notifyAll();
     
    // join them
    for(size_t i = 0;i<workers.size();++i)
        workers[i]->join();
}


// add new work item to the pool
template<class F>
void HTThreadPool::enqueue(F f)
{
    synchronized(queueMutex) 
    {
        // add the task
        tasks.push_back(std::function<void()>(f));
    } 
     
    // wake up one thread
    condition.notify();
}

NS_HT_END(Huta) 