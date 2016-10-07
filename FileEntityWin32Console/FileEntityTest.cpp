#include "stdafx.h"

#include "FileEntityTest.h"

bool FileEntityTest::GetTestSuccess()
{
    return testSuccess;
}

void FileEntityTest::FileEntityTest01()
{
    testSuccess = false;

    FileEntity * f = new FileEntity();
    f->SetDirectory(new string("E:\\Users\\b50061tem.NES00\\Desktop\\Desktop\\ì¬•¨\\Proj.1609"));
    f->SetFileName(new string("test.txt"));

    f->Prepare();
    if (!f->IsPrepared()) {
        cout << "FileEntityTest01 prepare failed." << "\n";
        delete f;
        return;
    }

    f->ReadFile();
    if (!f->IsReadSuccess()) {
        cout << "FileEntityTest01 read file failed." << "\n";
        delete f;
        return;
    }

    vector<char> * test = new vector<char>();
    test = f->GetFileContents();

    cout << "FileEntityTest01 success." << "\n";

    testSuccess = true;

    string value;
    cin >> value;
}

FileEntityTest::FileEntityTest()
{
}


FileEntityTest::~FileEntityTest()
{
}
