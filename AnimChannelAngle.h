/**
 * @file AnimChannelAngle.h
 * @author Noah Wolff
 *
 * Animation channel for angles.
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
#define CANADIANEXPERIENCE_ANIMCHANNELANGLE_H

#include "AnimChannel.h"


/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel {
protected:
    /// Class that represents a keyframe angle
    class KeyframeAngle : public Keyframe {
    private:
        /// Angle of Keyframe
        double mAngle;

        /// The channel this keyframe is associated with
        AnimChannelAngle *mChannel;

    public:
        /// Default constructor (disabled)
        KeyframeAngle() = delete;

        /// Copy constructor (disabled)
        KeyframeAngle(const KeyframeAngle &) = delete;

        /// Assignment operator
        void operator=(const KeyframeAngle &) = delete;

        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {}

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyframe 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }

        /**
         * Get the angle of the KeyFrame
         * @return Angle of the KeyFrame
         */
        double GetAngle() const { return mAngle; }

    };

    virtual void Tween(double t) override;

private:
    /// Angle of the channel
    double mAngle = 0;

    /// The first angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;

public:
    /// Default constructor
    AnimChannelAngle();

    /// Copy constructor (disabled)
    AnimChannelAngle(const AnimChannelAngle &) = delete;

    /// Assignment operator
    void operator=(const AnimChannelAngle &) = delete;



    void SetKeyframe(double angle);



    /**
     * Get the angle of the channel
     * @return Angle of the channel
     */
    double GetAngle() const { return mAngle; }

};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
