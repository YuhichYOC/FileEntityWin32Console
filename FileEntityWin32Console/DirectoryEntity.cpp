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
    string * path = new string();
    path->assign(*parentPath);
    path->append("\\");
    path->append(*StrFromWChar_t(parentFileInfo->cFileName));
    addDir->SetDirectory(path);

    unique_ptr<string> findPath(new string());
    findPath->assign(*path);
    findPath->append("\\*.*");
    LPCTSTR dirPath;
    dirPath = WChar_tFromStr(findPath.get());
    
    HANDLE ret;
    LPWIN32_FIND_DATA fileInfo = new WIN32_FIND_DATA();

    ret = FindFirstFile(dirPath, fileInfo);
    if (ret != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (WChar_tStartsWith(fileInfo->cFileName, new string(".\0")) || WChar_tStartsWith(fileInfo->cFileName, new string(".."))) {
                    continue;
                }
                addDir->AddDirectory(Describe(fileInfo, addDir->GetDirectory()));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(StrFromWChar_t(fileInfo->cFileName));
                addDir->AddFile(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

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
    unique_ptr<string> path(new string());
    path->assign(*directory.get());
    path->append("\\*.*");

    LPCTSTR dirPath;
    dirPath = WChar_tFromStr(path.get());
    
    HANDLE ret;
    LPWIN32_FIND_DATA fileInfo = new WIN32_FIND_DATA();
    
    ret = FindFirstFile(dirPath, fileInfo);
    if (ret != INVALID_HANDLE_VALUE) {
        do {
            if (fileInfo->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (WChar_tStartsWith(fileInfo->cFileName, new string(".\0")) || WChar_tStartsWith(fileInfo->cFileName, new string(".."))) {
                    continue;
                }
                subDirectories->push_back(Describe(fileInfo, directory.get()));
            }
            else {
                FileEntity * addFile = new FileEntity();
                addFile->SetFileName(StrFromWChar_t(fileInfo->cFileName));
                files->push_back(addFile);
            }
        } while (FindNextFile(ret, fileInfo));
    }

    delete fileInfo;
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
    if (directory.get() == nullptr) {
        dirPath = WChar_tFromStr(arg);
    }
    else {
        dirPath = WChar_tFromStr(&directory.get()->append("\\").append(*arg));
    }

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
