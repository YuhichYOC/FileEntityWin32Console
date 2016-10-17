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
    //f->SetDirectory(new string("E:\\Users\\b50061tem.NES00\\Desktop\\Desktop\\作成物\\Proj.1609"));
    //f->SetFileName(new string("TestMethod4 - コピー"));
    // うせやろ！！ new ない！！キモい！！
    f->SetDirectory(string("E:\\Users\\b50061tem.NES00\\Desktop\\Desktop\\作成物\\Proj.1609"));
    f->SetFileName(string("TestMethod4 - コピー"));

    f->ReadPrepare();
    if (!f->IsReadPrepared()) {
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

void FileEntityTest::FileEntityTest02()
{
    testSuccess = false;

    FileEntity * f = new FileEntity();
    //f->SetDirectory(new string("E:\\Users\\b50061tem.NES00\\Desktop\\Desktop\\作成物\\Proj.1609"));
    //f->SetFileName(new string("TestMethod4 - コピー"));
    f->SetDirectory(string("E:\\Users\\b50061tem.NES00\\Desktop\\Desktop\\作成物\\Proj.1609"));
    f->SetFileName(string("TestMethod4 - コピー"));

    f->ReadPrepare();
    if (!f->IsReadPrepared()) {
        cout << "FileEntityTest02 read prepare failed." << "\n";
        delete f;
        return;
    }

    f->ReadFile();
    if (!f->IsReadSuccess()) {
        cout << "FileEntityTest02 read file failed." << "\n";
        delete f;
        return;
    }

    FileEntity * o = new FileEntity();
    //o->SetDirectory(new string("E:\\Users\\b50061tem.NES00\\Desktop\\Desktop\\作成物\\Proj.1609"));
    //o->SetFileName(new string("TestMethod6 - コピー"));
    o->SetDirectory(string("E:\\Users\\b50061tem.NES00\\Desktop\\Desktop\\作成物\\Proj.1609"));
    o->SetFileName(string("TestMethod6 - コピー"));

    o->WritePrepare();
    if (!o->IsWritePrepared()) {
        cout << "FileEntityTest02 write prepare failed." << "\n";
        delete f;
        delete o;
        return;
    }
    o->SetFileContentsClone(f->GetFileContents());
    o->WriteFile();
    if (!o->IsWriteSuccess()) {
        cout << "FileEntityTest02 write file failed." << "\n";
        delete f;
        delete o;
        return;
    }

    cout << "FileEntityTest02 success." << "\n";

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