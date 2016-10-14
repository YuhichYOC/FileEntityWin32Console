#pragma once

#include "stdafx.h"

class WCharString
{
private:

    unique_ptr<string> value;

public:

    void Append(char * arg);

    void Append(wchar_t * arg);

    void Append(string * arg);

    void Append(const char * arg);

    void Append(const wchar_t * arg);

    void Append(const string * arg);

    WCharString * Value(char * arg);

    WCharString * Value(wchar_t * arg);

    WCharString * Value(string * arg);

    WCharString * Value(const char * arg);

    WCharString * Value(const wchar_t * arg);

    WCharString * Value(const string * arg);

    wchar_t ToWChar();

    string ToString();

    WCharString();

    ~WCharString();
};
