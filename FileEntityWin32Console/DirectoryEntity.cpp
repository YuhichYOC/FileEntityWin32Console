#include "stdafx.h"

#include "DirectoryEntity.h"

wchar_t * DirectoryEntity::WChar_tFromStr(string * arg)
{
    size_t retSize = arg->length() + 1;
    size_t convSize = 0;
    wchar_t * retVal = new wchar_t[retSize];
    mbstowcs_s(&convSize, retVal, retSize, arg->c_str(), _TRUNCATE);
    return retVal;
}

string * DirectoryEntity::StrFromWChar_t(wchar_t * arg)
{
    wstring castedArg = arg;
    size_t retSize = castedArg.length() + 1;
    size_t convSize = 0;
    char * arrayFromArg = new char[retSize];
    wcstombs_s(&convSize, arrayFromArg, retSize, arg, _TRUNCATE);
    string * retVal = new string(arrayFromArg);
    return retVal;
}

void DirectoryEntity::SetDirectory(string * arg)
{
    rootDirectoryFound = false;
    if (FindDir()) {
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
    return RootDirectoryFound;
}

void DirectoryEntity::CreateRootDirectory(string * arg)
{
    createSuccess = false;

    LPCWSTR dirPath;
    dirPath = WChar_tFromStr(arg);

    if (!FindDir()) {
        int ret = CreateDirectory(dirPath, nullptr);
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

    LPCWSTR dirPath;
    dirPath = WChar_tFromStr(directory.get());

    if (!FindDir()) {
        int ret = CreateDirectory(dirPath, nullptr);
        if (ret != 0) {
            createSuccess = true;
        }
    }
}

void DirectoryEntity::CreateDir(string * arg)
{
    createSuccess = false;

    LPCWSTR dirPath;
    dirPath = WChar_tFromStr(&directory.get()->append("\\").append(*arg));

    if (!FindDir()) {
        int ret = CreateDirectory(dirPath, nullptr);
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
    LPCWSTR dirPath;
    dirPath = WChar_tFromStr(directory.get());

    if (PathFileExists(dirPath)) {
        return true;
    }
    else {
        return false;
    }
}

bool DirectoryEntity::FindDir(string * arg)
{
    LPCWSTR dirPath;
    dirPath = WChar_tFromStr(&directory.get()->append("\\").append(*arg));

    if (PathFileExists(dirPath)) {
        return true;
    }
    else {
        return false;
    }
}

void DirectoryEntity::DeleteExistingDir()
{
    deleteSuccess = false;

    LPCWSTR dirPath;
    dirPath = WChar_tFromStr(directory.get());

    if (FindDir()) {
        int ret = RemoveDirectory(dirPath);
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

void DirectoryEntity::DeleteExistingDir(string * arg)
{
    deleteSuccess = false;

    LPCWSTR dirPath;
    dirPath = WChar_tFromStr(&directory.get()->append("\\").append(*arg));

    if (FindDir(arg)) {
        int ret = RemoveDirectory(dirPath);
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

DirectoryEntity::DirectoryEntity()
{
    directory = unique_ptr<string>();
    subDirectories = new vector<DirectoryEntity *>();
    files = new vector<FileEntity *>();
    disposed = false;
}

void DirectoryEntity::Dispose()
{
    for (size_t i = 0; i < subDirectories->size(); i++) {
        subDirectories->at(i)->Dispose();
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
