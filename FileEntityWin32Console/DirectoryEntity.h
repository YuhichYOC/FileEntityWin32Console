#pragma once

#include "stdafx.h"

#include "WCharString.h"

#include "FileEntity.h"

#pragma comment(lib, "ShLwApi.Lib")

class DirectoryEntity
{
private:

    string directoryName;

    string fullPath;

    vector<DirectoryEntity *> * subDirectories;

    vector<FileEntity *> * files;

    bool rootDirectoryFound;

    bool createSuccess;

    bool deleteSuccess;

    string dirCopyTo;

    bool useCopyRollback;

    bool copySuccess;

    bool disposed;

    DirectoryEntity * Describe(LPWIN32_FIND_DATA fileInfo, string parentPath);

    void DirCopy(DirectoryEntity * arg1subDir, string arg2path);

public:

    void SetDirectory(string arg);

    string GetDirectoryName();

    string GetFullPath();

    bool RootDirectoryFound();

    void Describe();

    void CreateRootDirectory(string arg);

    void SetDirectories(vector<DirectoryEntity *> * arg);

    vector<DirectoryEntity *> * GetDirectories();

    void AddDirectory(DirectoryEntity * arg);

    void SetFiles(vector<FileEntity *> * arg);

    vector<FileEntity *> * GetFiles();

    void AddFile(FileEntity * arg);

    bool IsCreateSuccess();

    bool IsDeleteSuccess();

    void CreateDir();

    void CreateDir(string arg);

    bool FindDir();

    bool FindDir(string arg);

    void DeleteExistingDir();

    void DeleteExistingDir(string arg);

    void DirCopy(string arg, bool rollback);

    DirectoryEntity();

    void Dispose();

    ~DirectoryEntity();
};