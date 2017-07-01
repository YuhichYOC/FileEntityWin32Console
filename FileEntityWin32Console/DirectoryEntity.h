/*
*
* DirectoryEntity.h
*
* Copyright 2016 Yuichi Yoshii
*     吉井雄一 @ 吉井産業  you.65535.kir@gmail.com
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