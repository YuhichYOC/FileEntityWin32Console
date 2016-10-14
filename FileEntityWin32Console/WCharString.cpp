#include "stdafx.h"

#include "WCharString.h"

WCharString * WCharString::Append(char * arg)
{
    value->append(arg);
    return this;
}

WCharString * WCharString::Append(wchar_t * arg)
{
    wstring castedArg = arg;
    size_t argSize = castedArg.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<char> mbArg(new char[argSize]);
    wcstombs_s(&cnvSize, mbArg.get(), argSize, arg, _TRUNCATE);
    value->append(mbArg.get());
    return this;
}

WCharString * WCharString::Append(string * arg)
{
    value->append(*arg);
    return this;
}

WCharString * WCharString::Append(const char * arg)
{
    value->append(arg);
    return this;
}

WCharString * WCharString::Append(const wchar_t * arg)
{
    wstring castedArg = arg;
    size_t argSize = castedArg.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<char> mbArg(new char[argSize]);
    wcstombs_s(&cnvSize, mbArg.get(), argSize, arg, _TRUNCATE);
    value->append(mbArg.get());
    return this;
}

WCharString * WCharString::Append(const string * arg)
{
    value->append(*arg);
    return this;
}

WCharString * WCharString::Value(char * arg)
{
    WCharString * ret = new WCharString();
    ret->Append(arg);
    return ret;
}

WCharString * WCharString::Value(wchar_t * arg)
{
    WCharString * ret = new WCharString();
    ret->Append(arg);
    return ret;
}

WCharString * WCharString::Value(string * arg)
{
    WCharString * ret = new WCharString();
    ret->Append(arg);
    return ret;
}

WCharString * WCharString::Value(const char * arg)
{
    WCharString * ret = new WCharString();
    ret->Append(arg);
    return ret;
}

WCharString * WCharString::Value(const wchar_t * arg)
{
    WCharString * ret = new WCharString();
    ret->Append(arg);
    return ret;
}

WCharString * WCharString::Value(const string * arg)
{
    WCharString * ret = new WCharString();
    ret->Append(arg);
    return ret;
}

wchar_t * WCharString::ToWChar()
{
    size_t retSize = value->length() + 1;
    size_t cnvSize = 0;
    wchar_t * ret = new wchar_t[retSize];
    mbstowcs_s(&cnvSize, ret, retSize, value->c_str(), _TRUNCATE);
    return ret;
}

string * WCharString::ToString()
{
    return value;
}

WCharString::WCharString()
{
    value = new string();
}

WCharString::~WCharString()
{
    delete value;
}