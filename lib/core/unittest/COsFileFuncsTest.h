/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */
#ifndef INCLUDED_COsFileFuncsTest_h
#define INCLUDED_COsFileFuncsTest_h

#include <cppunit/extensions/HelperMacros.h>


class COsFileFuncsTest : public CppUnit::TestFixture
{
    public:
        void testInode();
        void testLStat();

        static CppUnit::Test *suite();
};

#endif // INCLUDED_COsFileFuncsTest_h

