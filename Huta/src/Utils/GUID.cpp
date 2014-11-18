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

#include <Utils/GUID.h>

#include <iomanip>
#include <random>
#include <sstream> 

namespace Huta {

    // converts a single hex char to a number (0 - 15)
    unsigned char hexDigitToChar(char ch)
    {
      if (ch > 47 && ch < 58)
        return ch - 48;

      if (ch > 96 && ch < 103)
        return ch - 87;

      if (ch > 64 && ch < 71)
        return ch - 55;

      return 0;
    }

    // converts the two hexadecimal characters to an unsigned char (a byte)
    unsigned char hexPairToChar(char a, char b)
    {
      return hexDigitToChar(a) * 16 + hexDigitToChar(b);
    }

    // get random hexa
    unsigned char randomHexChar() {
        static const unsigned char hexDigits[] = "0123456789abcdef";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 16);
        unsigned char hex = hexDigits[dis(gen)];
        return hex;
    }

    // overload << so that it's easy to convert to a string
    std::ostream &operator<<(std::ostream &s, const GUID &guid)
    {
      return s << std::hex << std::setfill('0')
        << std::setw(2) << (int)guid._bytes[0]
        << std::setw(2) << (int)guid._bytes[1]
        << std::setw(2) << (int)guid._bytes[2]
        << std::setw(2) << (int)guid._bytes[3]
        << "-"
        << std::setw(2) << (int)guid._bytes[4]
        << std::setw(2) << (int)guid._bytes[5]
        << "-"
        << std::setw(2) << (int)guid._bytes[6]
        << std::setw(2) << (int)guid._bytes[7]
        << "-"
        << std::setw(2) << (int)guid._bytes[8]
        << std::setw(2) << (int)guid._bytes[9]
        << "-"
        << std::setw(2) << (int)guid._bytes[10]
        << std::setw(2) << (int)guid._bytes[11]
        << std::setw(2) << (int)guid._bytes[12]
        << std::setw(2) << (int)guid._bytes[13]
        << std::setw(2) << (int)guid._bytes[14]
        << std::setw(2) << (int)guid._bytes[15];
    }


    GUID::GUID(const std::vector<unsigned char> &bytes) {
        _bytes = bytes;
    }

    GUID::GUID(const unsigned char *bytes) {
        _bytes.assign(bytes, bytes + 16);
    }

    GUID::GUID(const std::string &fromString) {
        _bytes.clear();

        char charOne, charTwo;
        bool lookingForFirstChar = true;

        for(const char &ch : fromString) {
            if(ch == '-') {
                continue;
            }
            if(lookingForFirstChar) {
                charOne = ch;
                lookingForFirstChar = false;
            } else {
                charTwo = ch;
                auto byte = hexPairToChar(charOne, charTwo);
                _bytes.push_back(byte);
                lookingForFirstChar = true;
            }
        }
    }

    // Create empty guid
    GUID::GUID() {
        _bytes = std::vector<unsigned char>(16, 0);
    }


    GUID::GUID(const GUID& other) {
        _bytes = other._bytes;
    }

    std::string GUID::toString() {
        std::stringstream s;
        s << *this;
        return s.str();
    }

    // overload assignment operator
    GUID &GUID::operator=(const GUID &other) {
        _bytes = other._bytes;
        return *this;
    }
    
    bool GUID::operator==(const GUID &other) const {
        return _bytes == other._bytes;
    }
        
    bool GUID::operator!=(const GUID &other) const {
        return !((*this) == other);
    }


    GUIDGenerator::GUIDGenerator() {
    }

    GUID GUIDGenerator::createGUID() {
        // http://www.ietf.org/rfc/rfc4122.txt
        unsigned char bytes[16];
        for (int i = 0; i < 16; i++) {
            bytes[i] = hexPairToChar(randomHexChar(), randomHexChar());
        }
        // set version
        bytes[6] &= 0x4f;
        bytes[6] |= 0x40;

        // set variant
        bytes[8] &= 0xbf;   // 0b10111111
        bytes[8] |= 0x80;   // 0b10000000

        return GUID(bytes);
    }
}