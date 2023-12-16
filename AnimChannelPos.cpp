/**
 * @file AnimChannelPos.cpp
 * @author Noah Wolff
 */

#include "pch.h"
#include "AnimChannelPos.h"


/**
 * Constructor
 */
AnimChannelPos::AnimChannelPos() : AnimChannel()
{

}

/**
 * Set a keyframe
 *
 * This function allocates a new keyframe and sends it to
 * AnimChannel, which will insert it into the collection of keyframes.
 * @param position Position for the keyframe.
 */
void AnimChannelPos::SetKeyframe(wxPoint position)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the position
    auto keyframe = std::make_shared<KeyframePos>(this, position);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}

/**
 * Compute a position that is an interpolation
 * between two keyframes
 *
 * This function is called after Use1 and Use2,
 * so we have pointers to valid keyframes of the
 * type KeyframePos. This function computes the
 * tweening.
 *
 * @param t A t value. t=0 means keyframe1, t=1 means keyframe2.
 * Other values interpolate between.
 */
void AnimChannelPos::Tween(double t)
{
    mPosition = wxPoint(int(mKeyframe1->GetPosition().x + t * (mKeyframe2->GetPosition().x - mKeyframe1->GetPosition().x)),
                        int(mKeyframe1->GetPosition().y + t * (mKeyframe2->GetPosition().y - mKeyframe1->GetPosition().y)));
}
