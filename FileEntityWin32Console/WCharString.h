/*
*
* WCharString.h
*
* Copyright 2016 Yuichi Yoshii
*     吉井雄一 @ 吉井産業  you.65535.kir@gmail.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#pragma once

#include <codecvt>
#include <iostream>
#include <locale>
#include <memory>
#include <string>

#include <windows.h>

using namespace std;

class WCharString {
private:

    string v;

    string newvfromws(wstring arg);

    wstring wsfromv();

    int maxNullPosition;

    void Assign(char * arg);

    void Assign(unsigned char * arg);

    void Assign(wchar_t * arg);

    void Assign(string arg);

    void Assign(string * arg);

    void Assign(const char * arg);

    void Assign(const unsigned char * arg);

    void Assign(const wchar_t * arg);

    void Assign(const string * arg);

public:

    WCharString Append(char * arg);

    WCharString Append(unsigned char * arg);

    WCharString Append(wchar_t * arg);

    WCharString Append(string arg);

    WCharString Append(string * arg);

    WCharString Append(const char * arg);

    WCharString Append(const unsigned char * arg);

    WCharString Append(const wchar_t * arg);

    WCharString Append(const string * arg);

    WCharString Value(char * arg);

    WCharString Value(unsigned char * arg);

    WCharString Value(wchar_t * arg);

    WCharString Value(string arg);

    WCharString Value(string * arg);

    WCharString Value(const char * arg);

    WCharString Value(const unsigned char * arg);

    WCharString Value(const wchar_t * arg);

    WCharString Value(const string * arg);

    unique_ptr<wchar_t> ToWChar();

    string ToString();

    void SetMaxNullPosition(int arg);

    int NullPosition(char * arg);

    int NullPosition(unsigned char * arg);

    int NullPosition(wchar_t * arg);

    int NullPosition(const char * arg);

    int NullPosition(const unsigned char * arg);

    int NullPosition(const wchar_t * arg);

    bool WChar_tStartsWith(wchar_t * arg1eval, string arg2test);

    string SysErrMessage();

    WCharString();

    ~WCharString();
};