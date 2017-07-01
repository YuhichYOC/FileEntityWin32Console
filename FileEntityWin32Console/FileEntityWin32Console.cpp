/*
*
* FileEntityWin32Console.cpp
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

#include "DirectoryEntityTest.h"
#include "FileEntityTest.h"

void DirectoryEntityTest01()
{
    DirectoryEntityTest * dTest = new DirectoryEntityTest();
    dTest->DirectoryEntityTest01();
    if (dTest->GetTestSuccess()) {
        cout << "dTest 01 success." << "\n";
    }
    else {
        cout << "dTest 01 failed." << "\n";
    }
    delete dTest;
}

void DirectoryEntityTest02()
{
    DirectoryEntityTest * dTest = new DirectoryEntityTest();
    dTest->DirectoryEntityTest02();
    if (dTest->GetTestSuccess()) {
        cout << "dTest 02 success." << "\n";
    }
    else {
        cout << "dTest 02 failed." << "\n";
    }
    delete dTest;
}

void FileEntityTest01()
{
    FileEntityTest * fTest = new FileEntityTest();
    fTest->FileEntityTest01();
    if (fTest->GetTestSuccess()) {
        cout << "fTest 01 success." << "\n";
    }
    else {
        cout << "fTest 01 failed." << "\n";
    }
    delete fTest;
}

void FileEntityTest02()
{
    FileEntityTest * fTest = new FileEntityTest();
    fTest->FileEntityTest02();
    if (fTest->GetTestSuccess()) {
        cout << "fTest 02 success." << "\n";
    }
    else {
        cout << "fTest 02 failed." << "\n";
    }
    delete fTest;
}

int main()
{
    cout << "Test started." << "\n";

    /*
    FileEntityTest01();
    FileEntityTest02();
    DirectoryEntityTest01();
    */
    DirectoryEntityTest02();

    string value;
    cin >> value;

    return 0;
}