#include "gtest/gtest.h"
#include <igaBoundary.h>
#include <iostream>

using namespace basis;
using namespace matrix;

TEST( igaBoundary, BoxCorner_ParametersInto )
{
    igaVector<bool> param;

    BoxCorner bc1( 1 );
    bc1.ParametersInto( 2, param );
    EXPECT_EQ( param( 0 ), 0 );
    EXPECT_EQ( param( 1 ), 0 );

    BoxCorner bc2( 2 );
    bc2.ParametersInto( 2, param );
    EXPECT_EQ( param( 0 ), 1 );
    EXPECT_EQ( param( 1 ), 0 );

    BoxCorner bc3( 3 );
    bc3.ParametersInto( 2, param );
    EXPECT_EQ( param( 0 ), 0 );
    EXPECT_EQ( param( 1 ), 1 );

    BoxCorner bc4( 4 );
    bc4.ParametersInto( 2, param );
    EXPECT_EQ( param( 0 ), 1 );
    EXPECT_EQ( param( 1 ), 1 );
}

TEST( IndependentMethod, ResetsToZero2 )
{
    int i = 0;
    EXPECT_EQ( 0, i );
}

// The fixture for testing class Project1. From google test primer.
class BasisTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    BasisTest()
    {
        // You can do set-up work for each test here.
    }

    virtual ~BasisTest()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};