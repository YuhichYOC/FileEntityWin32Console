#pragma once

#include "stdafx.h"

class WCharString
{
private:

    string * value;

public:

    WCharString * Append(char * arg);

    WCharString * Append(wchar_t * arg);

    WCharString * Append(string * arg);

    WCharString * Append(const char * arg);

    WCharString * Append(const wchar_t * arg);

    WCharString * Append(const string * arg);

    WCharString * Value(char * arg);

    WCharString * Value(wchar_t * arg);

    WCharString * Value(string * arg);

    WCharString * Value(const char * arg);

    WCharString * Value(const wchar_t * arg);

    WCharString * Value(const string * arg);

    wchar_t * ToWChar();

    string * ToString();

    WCharString();

    ~WCharString();
};
