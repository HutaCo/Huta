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
#include <Core/HTObject.h>
#include <Core/HTArray.h>
#include <unordered_map>
#include <functional>
#include <sstream>

NS_HT_BEGIN(Huta)

class HTDictionary;
class HTDictionaryElement;


class HTDictionary: public HTObject, public HTClonable
{
public:
    // Create an empty dictionary
    static HTDictionary* create();

    // Create a dictionary with an existing dictionary
    static HTDictionary* createWithDictionary(HTDictionary* other);

    HTDictionary();
    ~HTDictionary();

    // Initialize the dictionary. Return true if initialization is successful
    bool init();

    // Get the count of elements in Dictionary
    size_t count();

    // Return all keys of elements
    HTArray* allKeys();

    // Return all values of elements
    HTArray* allObjects();

    // Get the object according to the specified key
    HTRef* objectForKey(HTRef* key);

    // Insert an object to dictionary, and match it with the specified key
    void setObject(HTRef* object, HTRef* key);

    // Remove an object by the specified key
    void removeObjectForKey(HTRef* key);

    // Remove objects by an array keys
    void removeObjectsForKeys(HTArray* keys);

    // Remove all objects in the dictionary
    void removeAllObjects();

    // Clone object
    HTDictionary* clone() const override;

private:
    
    struct KeyHasher
    {
        std::size_t operator()(const HTRefPtr<HTRef>& key) const
        {
            std::stringstream ss;
            ss << key.get();

            std::hash<std::string> hash;
            std::cout << key.get() << " " <<  hash(ss.str()) << std::endl;
            return hash(ss.str());
        }
    };
    std::unordered_map<HTRefPtr<HTRef>, HTRefPtr<HTRef>, KeyHasher> _map;
};

NS_HT_END(Huta)