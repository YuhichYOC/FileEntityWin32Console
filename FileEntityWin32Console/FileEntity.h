#pragma once

#include "stdafx.h"

#include "WCharString.h"

class FileEntity
{
private:

    string directory;

    string fileName;

    int fetchSize;

    ifstream * ifile;

    ofstream * ofile;

    int fileSize;

    vector<char> * fileContents;

    bool readPrepared;

    bool writePrepared;

    bool readSuccess;

    bool writeSuccess;

    bool deleteSuccess;

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

    void SetDirectory(string arg);

    string GetDirectory();

    void SetFileName(string arg);

    string GetFileName();

    void SetFetchSize(int arg);

    int GetFetchSize();

    void SetFileContents(vector<char> * arg);

    void SetFileContentsClone(vector<char> * arg);

    vector<char> * GetFileContents();

    bool IsReadPrepared();

    bool IsWritePrepared();

    bool IsReadSuccess();

    bool IsWriteSuccess();

    bool IsDeleteSuccess();

    void ReadPrepare();

    void WritePrepare();

    void ReadFile();

    void WriteFile();

    bool FindFile();

    void DeleteExistingFile();

    FileEntity();

    void Dispose();

    ~FileEntity();
};
