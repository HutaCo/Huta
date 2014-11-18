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

#include <Core/HTObject.h>
#include <Core/HTArray.h>

NS_HT_BEGIN(Huta)

class HTString: public HTObject, public HTClonable
{
public:
    HTString();

    HTString(const char* str);

    HTString(const std::string& str);

    HTString(const HTString& str);

    virtual ~HTString();

    // Override assignment operator
    HTString& operator=(const HTString& other);

    // Init a string with format
    bool initWithFormat(const char* format, ...);

    // Convert to int value
    int intValue() const;

    // Convert to unsigned int value
    unsigned int uintValue() const;

    // Convert to float value
    float floatValue() const;

    // Convert to double value
    double doubleValue() const;

    // Convert to bool value
    bool boolValue() const;

    // Get the C string
    const char* getCString() const;

    // Get the length of string
    size_t length() const;

    // Compare to a c string
    int compare(const char*) const;

    // Append additional characters at the end 
    void append(const std::string& str);

    // Append format additional character at the end 
    void appendFormat(const char* format, ...);

    virtual bool isEqual(const HTObject* other);

    // Split a string
    HTArray* componentsSeparatedByString(const char* delimiter);

    // Create a string with std string
    static HTString* create(const std::string& str);

    // Create a string with binary data
    static HTString* createWithData(const unsigned char* data, size_t len);

    // Create a string with format
    static HTString* createWithFormat(const char* format, ...);

    // Clonable
    virtual HTString* clone() const;

private:
    std::string _string;
};

NS_HT_END(Huta)