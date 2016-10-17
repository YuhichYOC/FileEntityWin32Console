#pragma once

#include "stdafx.h"

class WCharString
{
private:

    string * value;

    wchar_t * retWChar;

    void Assign(char * arg);

    void Assign(wchar_t * arg);

    void Assign(string * arg);

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

    WCharString WAppend(char * arg);

    WCharString WAppend(wchar_t * arg);

    WCharString WAppend(string * arg);

    WCharString WAppend(const char * arg);

    WCharString WAppend(const wchar_t * arg);

    WCharString WAppend(const string * arg);

    WCharString WValue(char * arg);

    WCharString WValue(wchar_t * arg);

    WCharString WValue(string * arg);

    WCharString WValue(const char * arg);

    WCharString WValue(const wchar_t * arg);

    WCharString WValue(const string * arg);

    wchar_t * ToWChar();

    string * ToString();

    WCharString();

    ~WCharString();
};
