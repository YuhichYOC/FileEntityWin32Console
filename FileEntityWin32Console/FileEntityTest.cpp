/*
*
* FileEntityTest.cpp
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