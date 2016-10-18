// FileEntityWin32Console.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

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