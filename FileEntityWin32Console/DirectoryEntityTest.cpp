/*
*
* DirectoryEntityTest.cpp
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