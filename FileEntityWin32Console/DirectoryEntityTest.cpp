#include "stdafx.h"

#include "DirectoryEntityTest.h"

bool DirectoryEntityTest::GetTestSuccess()
{
    return testSuccess;
}

void DirectoryEntityTest::DirectoryEntityTest01()
{
    testSuccess = false;

    unique_ptr<DirectoryEntity> d(new DirectoryEntity());
    d->SetDirectory(string("E:\\Tool\\aaa"));
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