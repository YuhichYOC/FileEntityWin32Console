#include "stdafx.h"

#include "DirectoryEntityTest.h"

bool DirectoryEntityTest::GetTestSuccess()
{
    return testSuccess;
}

void DirectoryEntityTest::DirectoryEntityTest01()
{
    testSuccess = false;

    DirectoryEntity * d = new DirectoryEntity();
    d->SetDirectory(new string("E:\\Tool\\SleepOut\\SleepOut"));
    d->Describe();

    cout << "Test 01 progress." << "\n";
    testSuccess = true;
}

DirectoryEntityTest::DirectoryEntityTest()
{
}

DirectoryEntityTest::~DirectoryEntityTest()
{
}
