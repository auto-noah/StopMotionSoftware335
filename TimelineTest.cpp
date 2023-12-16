/**
 * @file TimelineTest.cpp
 * @author Noah Wolff
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Timeline.h>
#include <AnimChannelAngle.h>
using namespace std;

TEST(TimelineTest, Construct) {
    // Create timeline
    Timeline timeline;
}

TEST(TimelineTest, NumFramesGetterSetter) {
    // Create timeline
    Timeline timeline;

    // Test default value
    ASSERT_EQ(timeline.GetNumFrames(), 300);

    // Set new value
    timeline.SetNumFrames(600);

    // Test for new value
    ASSERT_EQ(timeline.GetNumFrames(), 600);
}

TEST(TimelineTest, FrameRateGetterSetter) {
    // Create timeline
    Timeline timeline;

    // Test default value
    ASSERT_EQ(timeline.GetFrameRate(), 30);

    // Set new value
    timeline.SetFrameRate(60);

    // Test for new value
    ASSERT_EQ(timeline.GetFrameRate(), 60);
}

TEST(TimelineTest, CurrentTimeGetterSetter) {
    // Create timeline
    Timeline timeline;

    // Test default value
    ASSERT_NEAR(timeline.GetCurrentTime(), 0, 0.00001);

    // Set new value
    timeline.SetCurrentTime(1.5);

    // Test for new value
    ASSERT_NEAR(timeline.GetCurrentTime(), 1.5, 0.00001);
}

TEST(TimelineTest, GetDuration) {
    // Create timeline
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame) {
    // Create timeline
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());
}

