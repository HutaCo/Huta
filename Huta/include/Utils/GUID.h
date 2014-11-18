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

#pragma once
#include <vector>
#include <Core/HTMacros.h>
#include <Core/HTRef.h>

NS_HT_BEGIN(Huta)
class GUID {
public:
    GUID(const std::vector<unsigned char> &bytes);
    GUID(const unsigned char *bytes);
    GUID(const std::string &fromString);
    GUID();
    GUID(const GUID& other);

    std::string toString();

    GUID &operator=(const GUID &other);
    bool operator==(const GUID &other) const;
    bool operator!=(const GUID &other) const;
private:
    std::vector<unsigned char> _bytes;

    friend std::ostream &operator <<(std::ostream &stream, const GUID& guid);
};

class GUIDGenerator {
public:
    GUIDGenerator();

    GUID createGUID();
};
NS_HT_END(Huta)
