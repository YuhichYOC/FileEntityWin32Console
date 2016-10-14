#include "stdafx.h"

#include "DirectoryEntity.h"

bool DirectoryEntity::WChar_tStartsWith(wchar_t * arg1eval, string * arg2test)
{
    wstring castedArg1 = arg1eval;
    if (castedArg1.length() < arg2test->length()) {
        return false;
    }
    for (size_t i = 0; i < arg2test->length(); i++) {
        if (castedArg1.at(i) != arg2test->at(i)) {
            return false;
        }
    }
    return true;
}

DirectoryEntity * DirectoryEntity::Describe(LPWIN32_FIND_DATA parentFileInfo, string * parentPath)
{
    DirectoryEntity * addDir = new DirectoryEntity();
    addDir->SetDirectory(path->Value(parentPath)->Append("\\")->Append(parentFileInfo->cFileName)->ToString());

    HANDLE ret;
    LPWIN32_FIND_DATA fileInfo = new WIN32_FIND_DATA();

    ret = FindFirstFile((LPCWSTR)path->Value(parentPath)->Append("\\")->Append(parentFileInfo->cFileName)->Append("\\*.*")->ToWChar(), fileInfo);
    if (ret != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (WChar_tStartsWith(fileInfo->cFileName, &string(".\0")) || WChar_tStartsWith(fileInfo->cFileName, &string(".."))) {
                    continue;
                }
                addDir->AddDirectory(Describe(fileInfo, addDir->GetDirectory()));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(path->Value(fileInfo->cFileName)->ToString());
                addDir->AddFile(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

    delete fileInfo;
    return addDir;
}

void DirectoryEntity::SetDirectory(string * arg)
{
    rootDirectoryFound = false;
    if (FindDir(arg)) {
        directory.reset(arg);
        rootDirectoryFound = true;
    }
}

string * DirectoryEntity::GetDirectory()
{
    return directory.get();
}

bool DirectoryEntity::RootDirectoryFound()
{
    return rootDirectoryFound;
}

void DirectoryEntity::Describe()
{
    if (!rootDirectoryFound) {
        return;
    }

    HANDLE ret;
    LPWIN32_FIND_DATA fileInfo = new WIN32_FIND_DATA();

    ret = FindFirstFile((LPCWSTR)path->Value(directory.get())->Append("\\*.*")->ToWChar(), fileInfo);
    if (ret != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (WChar_tStartsWith(fileInfo->cFileName, &string(".\0")) || WChar_tStartsWith(fileInfo->cFileName, &string(".."))) {
                    continue;
                }
                subDirectories->push_back(Describe(fileInfo, directory.get()));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(path->Value(fileInfo->cFileName)->ToString());
                files->push_back(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

    delete fileInfo;
}

void DirectoryEntity::CreateRootDirectory(string * arg)
{
    createSuccess = false;

    if (!FindDir()) {
        int ret = CreateDirectory((LPCWSTR)path->Value(arg)->ToWChar(), nullptr);
        if (ret != 0) {
            createSuccess = true;
            directory.reset(arg);
        }
    }
}

void DirectoryEntity::SetDirectories(vector<DirectoryEntity *> * arg)
{
    subDirectories = arg;
}

vector<DirectoryEntity *> * DirectoryEntity::GetDirectories()
{
    return subDirectories;
}

void DirectoryEntity::AddDirectory(DirectoryEntity * arg)
{
    subDirectories->push_back(arg);
}

void DirectoryEntity::SetFiles(vector<FileEntity *> * arg)
{
    files = arg;
}

vector<FileEntity *> * DirectoryEntity::GetFiles()
{
    return files;
}

void DirectoryEntity::AddFile(FileEntity * arg)
{
    files->push_back(arg);
}

bool DirectoryEntity::IsCreateSuccess()
{
    return createSuccess;
}

bool DirectoryEntity::IsDeleteSuccess()
{
    return deleteSuccess;
}

void DirectoryEntity::CreateDir()
{
    createSuccess = false;

    if (!FindDir()) {
        int ret = CreateDirectory((LPCWSTR)path->Value(directory.get())->ToWChar(), nullptr);
        if (ret != 0) {
            createSuccess = true;
        }
    }
}

void DirectoryEntity::CreateDir(string * arg)
{
    createSuccess = false;

    if (!FindDir()) {
        int ret = CreateDirectory((LPCWSTR)path->Value(directory.get())->Append("\\")->Append(arg)->ToWChar(), nullptr);
        if (ret != 0) {
            createSuccess = true;
            DirectoryEntity * addDir = new DirectoryEntity();
            addDir->SetDirectory(arg);
            subDirectories->push_back(addDir);
        }
    }
}

bool DirectoryEntity::FindDir()
{
    if (PathFileExists((LPCWSTR)path->Value(directory.get())->ToWChar())) {
        return true;
    }
    else {
        return false;
    }
}

bool DirectoryEntity::FindDir(string * arg)
{
    if (directory.get() == nullptr) {
        if (PathFileExists((LPCWSTR)path->Value(arg)->ToWChar())) {
            return true;
        }
    }
    else {
        if (PathFileExists((LPCWSTR)path->Value(directory.get())->Append("\\")->Append(arg)->ToWChar())) {
            return true;
        }
    }
    return false;
}

void DirectoryEntity::DeleteExistingDir()
{
    deleteSuccess = false;

    if (FindDir()) {
        int ret = RemoveDirectory((LPCWSTR)path->Value(directory.get())->ToWChar());
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

void DirectoryEntity::DeleteExistingDir(string * arg)
{
    deleteSuccess = false;

    if (FindDir(arg)) {
        int ret = RemoveDirectory((LPCWSTR)path->Value(directory.get())->Append("\\")->Append(arg)->ToWChar());
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

DirectoryEntity::DirectoryEntity()
{
    directory = unique_ptr<string>();
    path = unique_ptr<WCharString>();
    subDirectories = new vector<DirectoryEntity *>();
    files = new vector<FileEntity *>();
    disposed = false;
}

void DirectoryEntity::Dispose()
{
    for (size_t i = 0; i < subDirectories->size(); i++) {
        delete subDirectories->at(i);
    }
    delete subDirectories;
    for (size_t j = 0; j < files->size(); j++) {
        delete files->at(j);
    }
    delete files;
    disposed = true;
}

DirectoryEntity::~DirectoryEntity()
{
    if (!disposed) {
        Dispose();
    }
}