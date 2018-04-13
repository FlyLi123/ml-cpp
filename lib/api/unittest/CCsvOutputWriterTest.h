/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */
#ifndef INCLUDED_CCsvOutputWriterTest_h
#define INCLUDED_CCsvOutputWriterTest_h

#include <cppunit/extensions/HelperMacros.h>

class CCsvOutputWriterTest : public CppUnit::TestFixture {
public:
    void testAdd();
    void testOverwrite();
    void testThroughput();
    void testExcelQuoting();
    void testNonExcelQuoting();

    static CppUnit::Test* suite();
};

#endif // INCLUDED_CCsvOutputWriterTest_h
