/**
 * @file AnimChannelPos.h
 * @author Noah Wolff
 *
 * Animation channel for positions.
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELPOS_H
#define CANADIANEXPERIENCE_ANIMCHANNELPOS_H

#include "AnimChannel.h"


/**
 * Animation channel for positions.
 */
class AnimChannelPos : public AnimChannel {
protected:
    /// Class that represents a keyframe position
    class KeyframePos : public Keyframe {
    private:
        /// Position of Keyframe
        wxPoint mPosition;

        /// The channel this keyframe is associated with
        AnimChannelPos *mChannel;

    public:
        /// Default constructor (disabled)
        KeyframePos() = delete;

        /// Copy constructor (disabled)
        KeyframePos(const KeyframePos &) = delete;

        /// Assignment operator
        void operator=(const KeyframePos &) = delete;

        /**
         * Constructor
         * @param channel The channel we are for
         * @param position The position for the keyframe
         */
        KeyframePos(AnimChannelPos *channel, wxPoint position) :
                Keyframe(channel), mChannel(channel), mPosition(position) {}

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyframe 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the position
        void UseOnly() override { mChannel->mPosition = mPosition; }

        /**
         * Get the position of the KeyFrame
         * @return Position of the KeyFrame
         */
        wxPoint GetPosition() const { return mPosition; }

    };

    virtual void Tween(double t) override;

private:
    /// Position of Keyframe
    wxPoint mPosition;

    /// The first position keyframe
    KeyframePos *mKeyframe1 = nullptr;

    /// The second position keyframe
    KeyframePos *mKeyframe2 = nullptr;

public:
    /// Default constructor
    AnimChannelPos();

    /// Copy constructor (disabled)
    AnimChannelPos(const AnimChannelPos &) = default;

    /// Assignment operator
    void operator=(const AnimChannelPos &) = delete;



    void SetKeyframe(wxPoint position);



    /**
     * Get the position of the channel
     * @return Position of the channel
     */
    wxPoint GetPosition() { return mPosition; }

};

#endif //CANADIANEXPERIENCE_ANIMCHANNELPOS_H
