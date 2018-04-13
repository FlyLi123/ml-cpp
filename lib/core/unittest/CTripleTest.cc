/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */
#include "CTripleTest.h"

#include <core/CLogger.h>
#include <core/CTriple.h>

#include <boost/unordered_map.hpp>

#include <string>

CppUnit::Test* CTripleTest::suite() {
    CppUnit::TestSuite* suiteOfTests = new CppUnit::TestSuite("CTripleTest");

    suiteOfTests->addTest(new CppUnit::TestCaller<CTripleTest>("CTripleTest::testOperators", &CTripleTest::testOperators));
    suiteOfTests->addTest(new CppUnit::TestCaller<CTripleTest>("CTripleTest::testBoostHashReady", &CTripleTest::testBoostHashReady));
    return suiteOfTests;
}

void CTripleTest::testOperators() {
    {
        // Assignment
        ml::core::CTriple<std::string, std::size_t, std::size_t> triple1("foo", 10, 8);
        ml::core::CTriple<std::string, std::size_t, std::size_t> triple2("bar", 5, 4);
        triple1 = triple2;
        CPPUNIT_ASSERT_EQUAL(std::string("bar"), triple1.first);
        CPPUNIT_ASSERT_EQUAL(std::size_t(5), triple1.second);
        CPPUNIT_ASSERT_EQUAL(std::size_t(4), triple1.third);
        CPPUNIT_ASSERT_EQUAL(std::string("bar"), triple2.first);
        CPPUNIT_ASSERT_EQUAL(std::size_t(5), triple2.second);
        CPPUNIT_ASSERT_EQUAL(std::size_t(4), triple2.third);
    }
    {
        // Test equality
        ml::core::CTriple<std::string, std::size_t, std::size_t> triple1("foo", 10, 8);
        ml::core::CTriple<std::string, std::size_t, std::size_t> triple2("foo", 10, 8);
        CPPUNIT_ASSERT(triple1 == triple2);
        CPPUNIT_ASSERT(triple1.hash() == triple2.hash());
    }
    {
        // Test inequality
        ml::core::CTriple<std::string, std::size_t, std::size_t> triple1("foo", 10, 8);
        ml::core::CTriple<std::string, std::size_t, std::size_t> triple2("foo", 10, 9);
        CPPUNIT_ASSERT(triple1 != triple2);
    }
    {
        // Test order comparisons
        ml::core::CTriple<std::string, std::size_t, std::size_t> triple1("foo", 10, 8);
        ml::core::CTriple<std::string, std::size_t, std::size_t> triple2("foo", 10, 9);
        CPPUNIT_ASSERT(triple1 < triple2);
        CPPUNIT_ASSERT(triple1 <= triple2);
        CPPUNIT_ASSERT(triple2 > triple1);
        CPPUNIT_ASSERT(triple2 >= triple1);
    }
}

void CTripleTest::testBoostHashReady() {
    using TStringSizeShortTriple = ml::core::CTriple<std::string, std::size_t, short>;
    using TStringSizeShortTripleSizeMap = boost::unordered_map<TStringSizeShortTriple, std::size_t>;

    TStringSizeShortTripleSizeMap map;
    map.emplace(ml::core::make_triple(std::string("foo"), std::size_t(10), short(3)), 1);
    map.emplace(ml::core::make_triple(std::string("bar"), std::size_t(20), short(4)), 2);

    CPPUNIT_ASSERT_EQUAL(std::size_t(1), map[ml::core::make_triple(std::string("foo"), std::size_t(10), short(3))]);
    CPPUNIT_ASSERT_EQUAL(std::size_t(2), map[ml::core::make_triple(std::string("bar"), std::size_t(20), short(4))]);
    CPPUNIT_ASSERT(map.find(ml::core::make_triple(std::string("bar"), std::size_t(20), short(8))) == map.end());
}
