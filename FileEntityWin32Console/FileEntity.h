#pragma once

#include "stdafx.h"

class FileEntity
{
private:

    unique_ptr<string> directory;

    unique_ptr<string> fileName;

    int fetchSize;

    ifstream * ifile;

    ofstream * ofile;

    int fileSize;

    vector<char> * fileContents;

    bool readPrepared;

    bool writePrepared;

    bool readSuccess;

    bool writeSuccess;

    bool disposed;

    int EvaluateFetchSize();

    int CountFileSize();

    int OptimizedFetchSize();

    void Fetch4();

    void Fetch16();

    void Fetch64();

    void Fetch256();

    void Fetch1024();

public:

    void SetDirectory(string * arg);

    string * GetDirectory();

    void SetFileName(string * arg);

    string * GetFileName();

    void SetFetchSize(int arg);

    int GetFetchSize();

    void SetFileContents(vector<char> * arg);

    void SetFileContentsClone(vector<char> * arg);

    vector<char> * GetFileContents();

    bool IsReadPrepared();

    bool IsWritePrepared();

    bool IsReadSuccess();

    bool IsWriteSuccess();

    void ReadPrepare();

    void WritePrepare();

    void ReadFile();

    void WriteFile();

    FileEntity();

    void Dispose();

    ~FileEntity();
};
