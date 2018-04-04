/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */

#ifndef INCLUDED_CTimeSeriesModelTest_h
#define INCLUDED_CTimeSeriesModelTest_h

#include <cppunit/extensions/HelperMacros.h>

class CTimeSeriesModelTest : public CppUnit::TestFixture
{
    public:
        void testClone(void);
        void testMode(void);
        void testAddBucketValue(void);
        void testAddSamples(void);
        void testPredict(void);
        void testProbability(void);
        void testWeights(void);
        void testMemoryUsage(void);
        void testPersist(void);
        void testUpgrade(void);
        void testAddSamplesWithCorrelations(void);
        void testProbabilityWithCorrelations(void);
        void testAnomalyModel(void);
        void testStepChangeDiscontinuities(void);
        void testLinearScaling(void);
        void testDaylightSaving(void);

        static CppUnit::Test *suite(void);
};

#endif // INCLUDED_CTimeSeriesModelTest_h
