/**
 * @file AnimChannel.h
 * @author Noah Wolff
 *
 * Base class for animation channels
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNEL_H
#define CANADIANEXPERIENCE_ANIMCHANNEL_H

class Timeline;


/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel {
protected:
    /// Default constructor
    AnimChannel() { }


    //
    // Keyframe
    //

    /// Class that represents a keyframe
    class Keyframe {
    private:
        /// Frame number
        int mFrame;

        /// Channel for the Frame
        AnimChannel* mChannel;

    protected:
        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}


    public:
        /// Default constructor (disabled)
        Keyframe() = delete;

        /// Copy constructor (disabled)
        Keyframe(const Keyframe &) = delete;

        /// Assignment operator
        void operator=(const Keyframe &) = delete;


        /// Virtual for use in derived Keyframe classes
        virtual void UseAs1() = 0;

        /// Virtual for use in derived Keyframe classes
        virtual void UseAs2() = 0;

        /// Virtual for use in derived Keyframe classes
        virtual void UseOnly() = 0;



        /**
         * Get the frame number
         * @return Frame number
         */
        int GetFrame() const { return mFrame; }

        /**
         * Set the frame number
         * @param frame Frame number value to set
         */
        void SetFrame(int frame) { mFrame = frame; }

    };

    void InsertKeyframe(std::shared_ptr<Keyframe> keyFrame);

    /**
     * Compute a position that is an interpolation
     * between two keyframes
     *
     * @param t A t value. t=0 means keyframe1, t=1 means keyframe2.
     * Other values interpolate between.
     */
    virtual void Tween(double t) = 0;

private:
    /// Name of the channel
    std::wstring mName;

    /// The timeline object
    Timeline* mTimeline = nullptr;

    /// Keyframe 1 value
    int mKeyframe1 = -1;

    /// Keyframe 2 value
    int mKeyframe2 = -1;

    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

public:
    /// Copy constructor (disabled)
    AnimChannel(const AnimChannel &) = delete;

    /// Assignment operator
    void operator=(const AnimChannel &) = delete;

    /// Virtual destructor
    virtual ~AnimChannel() {}



    bool IsValid();

    void SetFrame(int currFrame);



    /**
     * Get the name of the channel
     * @return Name of the channel
     */
    std::wstring GetName() const { return mName; };

    /**
     * Set the name of the channel
     * @param name Name to set
     */
    void SetName(const std::wstring& name) { mName = name; }

    /**
     * Get the Timeline
     * @return The timeline
     */
    Timeline* GetTimeline() const { return mTimeline; }

    /**
     * Set the timeline
     * @param timeline Timeline to set
     */
    void SetTimeline(Timeline* timeline) { mTimeline = timeline; }
};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
