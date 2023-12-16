/**
 * @file AnimChannelAngleTest.cpp
 * @author Noah Wolff
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>
using namespace std;

TEST(AnimChannelAngleTest, Construct) {
    AnimChannelAngle acl;
}

TEST(AnimChannelAngleTest, NameGetterSetter) {
    // Create a channel
    AnimChannelAngle acl;

    // Set a name
    acl.SetName(L"Jimbo");

    // Test for new name
    ASSERT_EQ(acl.GetName(), L"Jimbo");
}
