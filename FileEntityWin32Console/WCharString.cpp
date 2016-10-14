#include "stdafx.h"

#include "WCharString.h"

WCharString::WCharString()
{
    value = unique_ptr<string>();
}

WCharString::~WCharString()
{
}

void WCharString::Append(char * arg)
{
    value->append(arg);
}

void WCharString::Append(wchar_t * arg)
{
    wstring castedArg = arg;
    size_t argSize = castedArg.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<char> mbArg(new char[argSize]);
    wcstombs_s(&cnvSize, mbArg.get(), argSize, arg, _TRUNCATE);
    value->append(mbArg.get());
}

void WCharString::Append(string * arg)
{
    value->append(*arg);
}

void WCharString::Append(const char * arg)
{
    value->append(arg);
}

void WCharString::Append(const wchar_t * arg)
{
    wstring castedArg = arg;
    size_t argSize = castedArg.length() + 1;
    size_t cnvSize = 0;
    unique_ptr<char> mbArg(new char[argSize]);
    wcstombs_s(&cnvSize, mbArg.get(), argSize, arg, _TRUNCATE);
    value->append(mbArg.get());
}

void WCharString::Append(const string * arg)
{
    value->append(*arg);
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

wchar_t WCharString::ToWChar()
{
    size_t retSize = value->length() + 1;
    size_t cnvSize = 0;
    unique_ptr<wchar_t> ret(new wchar_t[retSize]);
    mbstowcs_s(&cnvSize, ret.get(), retSize, value->c_str(), _TRUNCATE);
    wchar_t retVal;
    retVal = *ret.get();
    return retVal;
}

string WCharString::ToString()
{
    return *value;
}