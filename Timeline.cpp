/**
 * @file Timeline.cpp
 * @author Noah Wolff
 */

#include "pch.h"
#include "Timeline.h"
#include "AnimChannel.h"


/**
 * Constructor
 */
Timeline::Timeline()
{
}

/**
 * Sets the current time
 *
 * Ensures all of the channels are
 * valid for that point in time.
 * @param t The new time to set
 */
void Timeline::SetCurrentTime(double t)
{
    mCurrentTime = t;
    mPointerLoc.x = (int)(mCurrentTime * mFrameRate * 4 + 10); //< I don't think this line should be here

    for (auto channel : mChannels)
    {
        channel->SetFrame(GetCurrentFrame());
    }
}

/**
 * Add a channel to the timeline
 * @param channel Channel to add
 */
void Timeline::AddChannel(AnimChannel* channel)
{
    mChannels.push_back(channel);
    channel->SetTimeline(this);
}
