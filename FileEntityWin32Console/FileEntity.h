/*
*
* FileEntity.h
*
* Copyright 2016 Yuichi Yoshii
*     ‹gˆä—Yˆê @ ‹gˆäŽY‹Æ  you.65535.kir@gmail.com
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
