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

class HTRef 
{
public:
    virtual HTRef* retain() = 0;

    virtual void release() = 0;

    virtual HTRef* autorelease() = 0;

    virtual unsigned int getReferenceCount() const = 0;

    virtual ~HTRef() {}
};

#define HT_REF_PTR_SAFE_RETAIN(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<HTRef*>(static_cast<const HTRef*>(ptr))->retain();\
        }\
    \
    }   while (0);

#define HT_REF_PTR_SAFE_RELEASE(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<HTRef*>(static_cast<const HTRef*>(ptr))->release();\
        }\
    \
    }   while (0);

#define HT_REF_PTR_SAFE_RELEASE_NULL(ptr)\
    \
    do\
    {\
        if (ptr)\
        {\
            const_cast<HTRef*>(static_cast<const HTRef*>(ptr))->release();\
            ptr = nullptr;\
        }\
    \
    }   while (0);

template <typename T> class HTRefPtr
{
public:
    
    inline HTRefPtr()
    :
        _ptr(nullptr)
    {
        
    }
    
    inline HTRefPtr(HTRefPtr<T> && other)
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    inline HTRefPtr(T * ptr)
    :
        _ptr(const_cast<typename std::remove_const<T>::type*>(ptr))     // Const cast allows RefPtr<T> to reference objects marked const too.
    {
        HT_REF_PTR_SAFE_RETAIN(_ptr);
    }
    
    inline HTRefPtr(std::nullptr_t ptr)
    :
        _ptr(nullptr)
    {
        
    }
    
    inline HTRefPtr(const HTRefPtr<T> & other)
    :
        _ptr(other._ptr)
    {
        HT_REF_PTR_SAFE_RETAIN(_ptr);
    }
    
    inline ~HTRefPtr()
    {
        HT_REF_PTR_SAFE_RELEASE_NULL(_ptr);
    }
    
    inline HTRefPtr<T> & operator = (const HTRefPtr<T> & other)
    {
        if (other._ptr != _ptr)
        {
            HT_REF_PTR_SAFE_RETAIN(other._ptr);
            HT_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other._ptr;
        }
        
        return *this;
    }
    
    inline HTRefPtr<T> & operator = (HTRefPtr<T> && other)
    {
        if (&other != this)
        {
            HT_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        
        return *this;
    }
    
    inline HTRefPtr<T> & operator = (T * other)
    {
        if (other != _ptr)
        {
            HT_REF_PTR_SAFE_RETAIN(other);
            HT_REF_PTR_SAFE_RELEASE(_ptr);
            _ptr = const_cast<typename std::remove_const<T>::type*>(other); 
        }
        
        return *this;
    }
    
    inline HTRefPtr<T> & operator = (std::nullptr_t other)
    {
        HT_REF_PTR_SAFE_RELEASE_NULL(_ptr);
        return *this;
    }
    
    // Note: using reinterpret_cast<> instead of static_cast<> here because it doesn't require type info.
    // Since we verify the correct type cast at compile time on construction/assign we don't need to know the type info
    // here. Not needing the type info here enables us to use these operations in inline functions in header files when
    // the type pointed to by this class is only forward referenced.
    
    inline operator T * () const { return reinterpret_cast<T*>(_ptr); }
    
    inline T & operator * () const
    {
        // TODO: throw exception if _ptr is NULL
        return reinterpret_cast<T&>(*_ptr);
    }
    
    inline T * operator->() const
    {
        // TODO: throw exception if _ptr is NULL
        return reinterpret_cast<T*>(_ptr);
    }
    
    inline T * get() const { return reinterpret_cast<T*>(_ptr); }
    
    
    inline bool operator == (const HTRefPtr<T> & other) const { return _ptr == other._ptr; }
    
    inline bool operator == (const T * other) const { return _ptr == other; }
    
    inline bool operator == (typename std::remove_const<T>::type * other) const { return _ptr == other; }
    
    inline bool operator == (const std::nullptr_t other) const { return _ptr == other; }
    
    
    inline bool operator != (const HTRefPtr<T> & other) const { return _ptr != other._ptr; }
    
    inline bool operator != (const T * other) const { return _ptr != other; }
    
    inline bool operator != (typename std::remove_const<T>::type * other) const { return _ptr != other; }
    
    inline bool operator != (const std::nullptr_t other) const { return _ptr != other; }
    
    
    inline bool operator > (const HTRefPtr<T> & other) const { return _ptr > other._ptr; }
    
    inline bool operator > (const T * other) const { return _ptr > other; }
    
    inline bool operator > (typename std::remove_const<T>::type * other) const { return _ptr > other; }
    
    inline bool operator > (const std::nullptr_t other) const { return _ptr > other; }
    
    
    inline bool operator < (const HTRefPtr<T> & other) const { return _ptr < other._ptr; }
    
    inline bool operator < (const T * other) const { return _ptr < other; }
    
    inline bool operator < (typename std::remove_const<T>::type * other) const { return _ptr < other; }
    
    inline bool operator < (const std::nullptr_t other) const { return _ptr < other; }
    
        
    inline bool operator >= (const HTRefPtr<T> & other) const { return _ptr >= other._ptr; }
    
    inline bool operator >= (const T * other) const { return _ptr >= other; }
    
    inline bool operator >= (typename std::remove_const<T>::type * other) const { return _ptr >= other; }
    
    inline bool operator >= (const std::nullptr_t other) const { return _ptr >= other; }
    
        
    inline bool operator <= (const HTRefPtr<T> & other) const { return _ptr <= other._ptr; }
    
    inline bool operator <= (const T * other) const { return _ptr <= other; }
    
    inline bool operator <= (typename std::remove_const<T>::type * other) const { return _ptr <= other; }
    
    inline bool operator <= (const std::nullptr_t other) const { return _ptr <= other; }
    
        
    inline operator bool() const { return _ptr != nullptr; }
        
    inline void reset()
    {
        HT_REF_PTR_SAFE_RELEASE_NULL(_ptr);
    }
        
    inline void swap(HTRefPtr<T> & other)
    {
        if (&other != this)
        {
            HTRef * tmp = _ptr;
            _ptr = other._ptr;
            other._ptr = tmp;
        }
    }
    

    inline void weakAssign(const HTRefPtr<T> & other)
    {
        HT_REF_PTR_SAFE_RELEASE(_ptr);
        _ptr = other._ptr;
    }
    
private:
    HTRef * _ptr;
};
    
/**
 * Cast between HTRefPtr types statically.
 */
template<class T, class U> HTRefPtr<T> static_pointer_cast(const HTRefPtr<U> & r)
{
    return HTRefPtr<T>(static_cast<T*>(r.get()));
}

/**
 * Cast between RefPtr types dynamically.
 */
template<class T, class U> HTRefPtr<T> dynamic_pointer_cast(const HTRefPtr<U> & r)
{
    return HTRefPtr<T>(dynamic_cast<T*>(r.get()));
}

/**
 * Done with these macros.
 */
#undef HT_REF_PTR_SAFE_RETAIN
#undef HT_REF_PTR_SAFE_RELEASE
#undef HT_REF_PTR_SAFE_RELEASE_NULL

NS_HT_END(Huta)