// FileEntityWin32Console.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include "FileEntityTest.h"

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
}

int main()
{
    FileEntityTest01();
    return 0;
}