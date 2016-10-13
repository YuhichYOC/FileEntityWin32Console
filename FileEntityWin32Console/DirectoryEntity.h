#pragma once

#include "stdafx.h"

#include "FileEntity.h"

#pragma comment(lib, "ShLwApi.Lib")

class DirectoryEntity
{
private:

    unique_ptr<string> directory;

    vector<DirectoryEntity *> * subDirectories;

    vector<FileEntity *> * files;

    bool rootDirectoryFound;

    bool createSuccess;

    bool deleteSuccess;

    unique_ptr<string> dirCopyTo;

    bool useCopyRollback;

    bool disposed;

    wchar_t * WChar_tFromStr(string * arg);

    string * StrFromWChar_t(wchar_t * arg);

    bool WChar_tStartsWith(wchar_t * arg1eval, string * arg2test);

    DirectoryEntity * Describe(LPWIN32_FIND_DATA fileInfo, string * parentPath);

public:

    void SetDirectory(string * arg);

    string * GetDirectory();

    bool RootDirectoryFound();

    void Describe();

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

    void DirCopy(string * arg, bool rollback);

    DirectoryEntity();

    void Dispose();

    ~DirectoryEntity();
};

