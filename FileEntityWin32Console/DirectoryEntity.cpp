#include "stdafx.h"

#include "DirectoryEntity.h"

DirectoryEntity * DirectoryEntity::Describe(LPWIN32_FIND_DATA parentFileInfo, string parentPath)
{
    WCharString path;

    DirectoryEntity * addDir = new DirectoryEntity();
    addDir->SetDirectory(path.Value(parentPath).Append("\\").Append(parentFileInfo->cFileName).ToString());

    HANDLE ret;
    LPWIN32_FIND_DATA fileInfo = new WIN32_FIND_DATA();

    unique_ptr<wchar_t> findPath = move(path.Value(parentPath).Append("\\").Append(parentFileInfo->cFileName).Append("\\*.*").ToWChar());
    ret = FindFirstFile((LPCWSTR)findPath.get(), fileInfo);
    if (ret != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (path.WChar_tStartsWith(fileInfo->cFileName, string(".\0")) || path.WChar_tStartsWith(fileInfo->cFileName, string(".."))) {
                    continue;
                }
                addDir->AddDirectory(Describe(fileInfo, addDir->GetDirectory()));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(path.Value(fileInfo->cFileName).ToString());
                addDir->AddFile(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

    delete fileInfo;
    return addDir;
}

void DirectoryEntity::SetDirectory(string arg)
{
    rootDirectoryFound = false;
    if (FindDir(arg)) {
        directory.assign(arg);
        rootDirectoryFound = true;
    }
}

string DirectoryEntity::GetDirectory()
{
    return directory;
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

    WCharString path;
    unique_ptr<wchar_t> findPath = move(path.Value(directory).Append("\\*.*").ToWChar());
    ret = FindFirstFile((LPCWSTR)findPath.get(), fileInfo);
    if (ret != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (path.WChar_tStartsWith(fileInfo->cFileName, string(".\0")) || path.WChar_tStartsWith(fileInfo->cFileName, string(".."))) {
                    continue;
                }
                subDirectories->push_back(Describe(fileInfo, directory));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(path.Value(fileInfo->cFileName).ToString());
                files->push_back(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

    delete fileInfo;
}

void DirectoryEntity::CreateRootDirectory(string arg)
{
    createSuccess = false;

    if (!FindDir()) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(arg).ToWChar());
        int ret = CreateDirectory((LPCWSTR)dirPath.get(), nullptr);
        if (ret != 0) {
            createSuccess = true;
            directory.assign(arg);
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
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(directory).ToWChar());
        int ret = CreateDirectory((LPCWSTR)dirPath.get(), nullptr);
        if (ret != 0) {
            createSuccess = true;
        }
    }
}

void DirectoryEntity::CreateDir(string arg)
{
    createSuccess = false;

    if (!FindDir()) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(directory).Append("\\").Append(arg).ToWChar());
        int ret = CreateDirectory((LPCWSTR)dirPath.get(), nullptr);
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
    WCharString path;
    unique_ptr<wchar_t> dirPath = move(path.Value(directory).ToWChar());
    if (PathFileExists((LPCWSTR)dirPath.get())) {
        return true;
    }
    else {
        return false;
    }
}

bool DirectoryEntity::FindDir(string arg)
{
    if (directory.empty()) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(arg).ToWChar());
        if (PathFileExists((LPCWSTR)dirPath.get())) {
            return true;
        }
    }
    else {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(directory).Append("\\").Append(arg).ToWChar());
        if (PathFileExists((LPCWSTR)dirPath.get())) {
            return true;
        }
    }
    return false;
}

void DirectoryEntity::DeleteExistingDir()
{
    deleteSuccess = false;

    if (FindDir()) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(directory).ToWChar());
        int ret = RemoveDirectory((LPCWSTR)dirPath.get());
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

void DirectoryEntity::DeleteExistingDir(string arg)
{
    deleteSuccess = false;

    if (FindDir(arg)) {
        WCharString path;
        unique_ptr<wchar_t> dirPath = move(path.Value(directory).Append("\\").Append(arg).ToWChar());
        int ret = RemoveDirectory((LPCWSTR)dirPath.get());
        if (ret != 0) {
            deleteSuccess = true;
        }
    }
}

DirectoryEntity::DirectoryEntity()
{
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