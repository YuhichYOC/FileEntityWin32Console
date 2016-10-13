#pragma once

#include "stdafx.h"

#include "FileEntity.h"

class DirectoryEntity
{
private:

    unique_ptr<string> directory;

    vector<DirectoryEntity *> * subDirectories;

    vector<FileEntity *> * files;

    bool rootDirectoryFound;

    bool createSuccess;

    bool deleteSuccess;

    bool disposed;

    wchar_t * WChar_tFromStr(string * arg);

    string * StrFromWChar_t(wchar_t * arg);

public:

    void SetDirectory(string * arg);

    string * GetDirectory();

    bool RootDirectoryFound();

    void CreateRootDirectory(string * arg);

    void SetDirectories(vector<DirectoryEntity *> * arg);

    vector<DirectoryEntity *> * GetDirectories();

    void AddDirectory(DirectoryEntity * arg);

    void SetFiles(vector<FileEntity *> * arg);

    vector<FileEntity *> * GetFiles();

    void AddFile(FileEntity * arg);

    bool IsCreateSuccess();

    bool IsDeleteSuccess();

    void CreateDir();

    void CreateDir(string * arg);

    bool FindDir();
    
    bool FindDir(string * arg);

    void DeleteExistingDir();

    void DeleteExistingDir(string * arg);

    DirectoryEntity();

    void Dispose();

    ~DirectoryEntity();
};

