#pragma once

#include "stdafx.h"

class FileEntity
{
private:

    unique_ptr<string> directory;

    unique_ptr<string> fileName;

    int fetchSize;

    ifstream * file;

    unique_ptr<vector<char>> fileContents;

    bool prepared;

    bool readSuccess;

    bool disposed;

    int EvaluateFetchSize();

    int CountFileSize();

    int OptimizedFetchSize();

    void Fetch4();

    void Fetch16();

    void Fetch64();

    void Fetch256();

    void Fetch1024();
    
    void Fetch(char readBuffer[], int size);

public:

    void SetDirectory(string * arg);

    string * GetDirectory();

    void SetFileName(string * arg);

    string * GetFileName();

    void SetFetchSize(int arg);

    void Prepare();

    bool IsPrepared();

    void ReadFile();

    bool IsReadSuccess();

    vector<char> * GetFileContents();

    FileEntity();

    void Dispose();

    ~FileEntity();
};

