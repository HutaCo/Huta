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

#include <Core/HTString.h>
#include <stdarg.h>
#include <regex>

NS_HT_BEGIN(Huta)

#define kMaxStringLen (1024*100)

std::string stringWithFormat(const char* format, va_list ap)
{
    char* p = new char[kMaxStringLen];
    if(p != nullptr) 
    {
        vsnprintf(p, kMaxStringLen, format, ap);
        std::string string(p);
        delete []p;
        return string;
    }
    return std::string("");
}

HTString::HTString() 
    :_string("")
{}

HTString::HTString(const char* str)
    :_string(str)
{}

HTString::HTString(const std::string& str)
    :_string(str)
{}

HTString::HTString(const HTString& str)
    :_string(str.getCString())
{}

HTString::~HTString()
{
    _string.clear();
}

HTString& HTString::operator=(const HTString& other)
{
    if(this != &other)
    {
        _string = other._string;
    }

    return *this;
}

bool HTString::initWithFormat(const char* format, ...)
{
    bool ret;
    va_list ap;
    va_start(ap, format);
    _string = stringWithFormat(format, ap);
    va_end(ap);

    return ret;
}

int HTString::intValue() const 
{
    return std::stoi(_string);
}

unsigned int HTString::uintValue() const
{
    return (unsigned int) intValue();
}

float HTString::floatValue() const
{
    return std::stof(_string);
}

double HTString::doubleValue() const 
{
    return std::stod(_string);
}

bool HTString::boolValue() const
{
    if(length() == 0)
    {
        return false;
    }

    if(strcmp(_string.c_str(), "0") == 0 || strcmp(_string.c_str(), "false"))
    {
        return false;
    }
    return true;
}

const char* HTString::getCString() const
{
    return _string.c_str();
}
 
size_t HTString::length() const 
{
    return _string.length();
}

int HTString::compare(const char* str) const
{
    return strcmp(getCString(), str);
}

void HTString::append(const std::string& str)
{
    _string.append(str);
}

void HTString::appendFormat(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    char* p = new char[kMaxStringLen];

    if(p != nullptr)
    {
        vsnprintf(p, kMaxStringLen, format, ap);
        _string.append(p);
        delete []p;
    }

    va_end(ap);
}

bool HTString::isEqual(const HTObject* object)
{
    bool ret = false;
    const HTString* pStr = dynamic_cast<const HTString*> (object);
    if(pStr != nullptr)
    {
        if(_string.compare(pStr->_string) == 0)
        {
            ret = true;
        }
    }
    return ret;
}

HTArray* HTString::componentsSeparatedByString(const char* delimiter)
{
    HTArray* array = HTArray::create();
    std::regex regex(delimiter);
    std::sregex_token_iterator 
        first{std::begin(_string), std::end(_string), regex, -1}, last;
    for(auto it = first; it != last; it++)
    {
        array->addObject(HTString::create(*it));
    }
    return array;
}

HTString* HTString::create(const std::string& str)
{
    HTString* object = new HTString(str);
    if(object)
    {
        object->autorelease();
    } 
    else 
    {
        delete object;
    }
    return object;
}

HTString* HTString::createWithData(const unsigned char* data, size_t len)
{
    HTString* string = nullptr;
    if(data != nullptr)
    {
        char* p = new char[len + 1];
        if(p != nullptr)
        {
            p[len] = '\0';
            if(len > 0)
            {
                memcpy(p, data, len);
            }
            string = HTString::create(p);
            delete []p;
        }
    }
    return string;
}

HTString* HTString::createWithFormat(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    HTString* string = HTString::create(stringWithFormat(format, ap));
    va_end(ap);
    return string;
}

HTString* HTString::clone() const
{
    return HTString::create(_string);
}

NS_HT_END(Huta)
