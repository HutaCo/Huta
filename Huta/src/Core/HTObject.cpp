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

#include <Core/HTObject.h>
#include <Core/HTAutoreleasePool.h>
#include <Core/HTString.h>

#include <sstream>
#include <algorithm>    // std::find
#include <list>

NS_HT_BEGIN(Huta)
#ifdef HT_MEM_LEAK_TRACK
static void trackRef(HTRef* ref);
static void untrackRef(HTRef* ref);
#endif


HTObject::HTObject() 
: _referenceCount(1)
{
#ifdef HT_MEM_LEAK_TRACK
    trackRef(this);
#endif
}

HTObject::~HTObject()
{
#ifdef HT_MEM_LEAK_TRACK
    if(_referenceCount != 0)
        untrackRef(this);
#endif
}

HTObject* HTObject::retain()
{
    ++_referenceCount;
    return this;
}

void HTObject::release()
{
    --_referenceCount;
    if(_referenceCount == 0)
    {
#ifdef HT_MEM_LEAK_TRACK
        untrackRef(this);
#endif
        delete this;
    }
}

bool HTObject::isEqual(const HTObject* other) 
{
    return (other == this);
}

HTObject* HTObject::autorelease()
{
    HTPoolManager::getInstance()->getCurrentPool()->addObject(this);
    return this;
}

unsigned int HTObject::getReferenceCount() const
{
    return _referenceCount;
}

HTString* HTObject::toString() const
{
    std::stringstream ss;
    ss << this;
    return HTString::create(ss.str());
}

#ifdef HT_MEM_LEAK_TRACK

static std::list<HTRef*> __refAllocationList;

void HTObject::printLeaks()
{
    // Dump Ref object memory leaks
    if (__refAllocationList.empty())
    {
        fprintf(stderr,"[memory] All Ref objects successfully cleaned up (no leaks detected).\n");
    }
    else
    {
        fprintf(stderr,"[memory] WARNING: %d Ref objects still active in memory.\n", (int)__refAllocationList.size());

        for (const auto& ref : __refAllocationList)
        {
            const char* type = typeid(*ref).name();
            fprintf(stderr,"[memory] LEAK: Ref object '%s' still active with reference count %d.\n", (type ? type : ""), ref->getReferenceCount());
        }
    }
}

static void trackRef(HTRef* ref)
{
    // Create memory allocation record.
    __refAllocationList.push_back(ref);
}

static void untrackRef(HTRef* ref)
{
    auto iter = std::find(__refAllocationList.begin(), __refAllocationList.end(), ref);
    if (iter == __refAllocationList.end())
    {
        fprintf(stderr, "[memory] CORRUPTION: Attempting to free (%s) with invalid ref tracking record.\n", typeid(*ref).name());
        return;
    }

    __refAllocationList.erase(iter);
}
#endif
NS_HT_END(Huta)