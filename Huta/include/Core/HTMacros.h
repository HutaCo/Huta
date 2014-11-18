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

#include <iostream>

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if(pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

// generic macros

// namespace
#define NS_HT_BEGIN(name)       namespace name {
#define NS_HT_END(name)         }
#define NS_HT_BEGIN_2(n1, n2)   namespace n1 { namespace n2 { 
#define NS_HT_END_2(n1, n2)     } }
#define NS_HT_BEGIN_3(n1, n2, n3)   namespace n1 { namespace n2 { namespace n3 {
#define NS_HT_END_3(n1, n2, n3)     } } }
#define NS_USING(name)              using namespace name;
#define NS_USING_2(n1, n2)          using namespace n1; using namespace n2;
#define NS_USING_3(n1, n2, n3)      using namespace n1; using namespace n2; using namespace n3;

// properties
#define HT_PROPERTY(varType, varName, funName)\
protected: varType varName; \
public: virtual const varType& get##funName(void) const;\
public: virtual void set##funName(const varType& var);


#define HT_PROPERTY_READONLY(varType, varName, funName) \
protected: varType varName;\
public: virtual varType get##funName(void) const;

// synthesize
#define HT_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#define HT_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }

#define HT_SYNTHESIZE_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }

#define HT_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }\
public: virtual void set##funName(const varType& var){ varName = var; }

#define HT_SYNTHESIZE_RETAIN(varType, varName, funName)    \
private: varType varName; \
public: virtual varType get##funName(void) const { return varName; } \
public: virtual void set##funName(varType var)   \
{ \
    if (varName != var) \
    { \
        HT_SAFE_RETAIN(var); \
        HT_SAFE_RELEASE(varName); \
        varName = var; \
    } \
} 

#define HT_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define HT_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define HT_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define HT_SAFE_RELEASE(p)          do { if(p) { (p)->release(); } } while(0)
#define HT_SAFE_RELEASE_NULL(p)     do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define HT_SAFE_RETAIN(p)           do { if(p) { (p)->retain(); } } while(0)



/*
 * only certain compilers support __attribute__((deprecated))
 */
#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
    #define HT_DEPRECATED_ATTRIBUTE __attribute__((deprecated))
#elif _MSC_VER >= 1400 //vs 2005 or higher
    #define HT_DEPRECATED_ATTRIBUTE __declspec(deprecated) 
#else
    #define HT_DEPRECATED_ATTRIBUTE
#endif 

#ifdef __GNUC__
#define HT_UNUSED __attribute__ ((unused))
#else
#define HT_UNUSED
#endif


#ifndef HT_REQUIRES_NULL_TERMINATION
    #if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
        #define HT_REQUIRES_NULL_TERMINATION __attribute__((sentinel(0,1)))
    #elif defined(__GNUC__)
        #define HT_REQUIRES_NULL_TERMINATION __attribute__((sentinel))
    #else
        #define HT_REQUIRES_NULL_TERMINATION
    #endif
#endif
