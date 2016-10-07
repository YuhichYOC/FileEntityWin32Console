#include "stdafx.h"

#include "FileEntity.h"

void FileEntity::SetDirectory(string * arg)
{
    directory.reset(arg);
}

string * FileEntity::GetDirectory()
{
    return directory.get();
}

void FileEntity::SetFileName(string * arg)
{
    fileName.reset(arg);
}

string * FileEntity::GetFileName()
{
    return fileName.get();
}

void FileEntity::SetFetchSize(int arg)
{
    fetchSize = arg;
}

void FileEntity::Prepare()
{
    string fullPath;
    fullPath.append(*directory.get());
    fullPath.append("\\");
    fullPath.append(*fileName.get());
    
    file = new ifstream(fullPath, ios::in | ios::binary);

    if (file) {
        prepared = true;
    }
    else {
        prepared = false;
    }
}

bool FileEntity::IsPrepared()
{
    return prepared;
}

int FileEntity::EvaluateFetchSize()
{
    if (fetchSize <= 0) {
        return OptimizedFetchSize();
    }
    else if (fetchSize <= 4) {
        return 4;
    }
    else if (fetchSize <= 16) {
        return 16;
    }
    else if (fetchSize <= 64) {
        return 64;
    }
    else if (fetchSize <= 256) {
        return 256;
    }
    else {
        return 1024;
    }
}

int FileEntity::CountFileSize()
{
    file->seekg(0, istream::end);
    streamoff endPos = file->tellg();
    file->seekg(0, istream::beg);
    streamoff startPos = file->tellg();

    return (int)(endPos - startPos);
}

int FileEntity::OptimizedFetchSize()
{
    int fileSize = CountFileSize();

    int mod4 = fileSize % 4;
    int mod16 = fileSize % 16;
    int mod64 = fileSize % 64;
    int mod256 = fileSize % 256;
    int mod1024 = fileSize % 1024;

    int div4 = (int)ceil((float)fileSize / 4);
    int div16 = (int)ceil((float)fileSize / 16);
    int div64 = (int)ceil((float)fileSize / 64);
    int div256 = (int)ceil((float)fileSize / 256);
    int div1024 = (int)ceil((float)fileSize / 1024);

    float score4 = (float)mod4 + (float)(div4 * div4) - (float)(0.25);
    float score16 = (float)mod16 + (float)(div16 * div16) - (float)(0.0625);
    float score64 = (float)mod64 + (float)(div64 * div64) - (float)(0.015625);
    float score256 = (float)mod256 + (float)(div256 * div256) - (float)(0.00390625);
    float score1024 = (float)mod1024 + (float)(div1024 * div1024) - (float)(0.0009765625);

    vector<float> scores;
    scores.push_back(score4);
    scores.push_back(score16);
    scores.push_back(score64);
    scores.push_back(score256);
    scores.push_back(score1024);
    
    sort(scores.begin(), scores.end());
    if (scores.at(0) == score4) {
        return 4;
    }
    else if (scores.at(0) == score16) {
        return 16;
    }
    else if (scores.at(0) == score64) {
        return 64;
    }
    else if (scores.at(0) == score256) {
        return 256;
    }
    else {
        return 1024;
    }
}

void FileEntity::Fetch4()
{
    char readBuffer[4];
    Fetch(readBuffer, 4);
}

void FileEntity::Fetch16()
{
    char readBuffer[16];
    Fetch(readBuffer, 16);
}

void FileEntity::Fetch64()
{
    char readBuffer[64];
    Fetch(readBuffer, 64);
}

void FileEntity::Fetch256()
{
    char readBuffer[256];
    Fetch(readBuffer, 256);
}

void FileEntity::Fetch1024()
{
    char readBuffer[1024];
    Fetch(readBuffer, 1024);
}

void FileEntity::Fetch(char readBuffer[], int size)
{
    while (!file->eof()) {
        file->read(readBuffer, size);
        fileContents->push_back(*readBuffer);
    }
}

void FileEntity::ReadFile()
{
    readSuccess = false;

    switch (EvaluateFetchSize())
    {
    case 4:
        Fetch4();
        break;
    case 16:
        Fetch16();
        break;
    case 64:
        Fetch64();
        break;
    case 256:
        Fetch256();
        break;
    default:
        Fetch1024();
        break;
    }
    file->close();

    readSuccess = true;
}

bool FileEntity::IsReadSuccess()
{
    return readSuccess;
}

vector<char> * FileEntity::GetFileContents()
{
    return fileContents.get();
}

FileEntity::FileEntity()
{
    directory = unique_ptr<string>();
    fileName = unique_ptr<string>();
    fetchSize = -1;
    file = nullptr;
    fileContents = unique_ptr<vector<char>>();
    disposed = false;
}

void FileEntity::Dispose()
{
    if (prepared) {
        file->close();
        delete file;
    }
    disposed = true;
}

FileEntity::~FileEntity()
{
    if (!disposed) {
        Dispose();
    }
}
