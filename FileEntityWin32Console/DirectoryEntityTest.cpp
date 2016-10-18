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

    testSuccess = true;
}

void DirectoryEntityTest::DirectoryEntityTest02()
{
    testSuccess = false;

    unique_ptr<DirectoryEntity> d(new DirectoryEntity());
    d->SetDirectory(string("E:\\Tool\\aaa"));
    d->Describe();

    d->DirCopy(string("E:\\Tool\\eee"), true);

    testSuccess = true;
}

DirectoryEntityTest::DirectoryEntityTest()
{
}

DirectoryEntityTest::~DirectoryEntityTest()
{
}