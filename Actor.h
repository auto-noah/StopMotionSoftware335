/**
 * @file Actor.h
 * @author Noah Wolff
 *
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */

#ifndef CANADIANEXPERIENCE_ACTOR_H
#define CANADIANEXPERIENCE_ACTOR_H

class Drawable;
class Picture;
#include "AnimChannelPos.h"
#include <vector>


/**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class Actor {
private:
    /// Name of Actor
    std::wstring mName;

    /// X, Y Position
    wxPoint mPosition = wxPoint(0, 0);

    /// Enabled status
    bool mEnabled = true;

    /// Clickable status
    bool mClickable = true;

    /// The root drawable
    std::shared_ptr<Drawable> mRoot;

    /// Vector of drawables
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;

    /// The Picture this Actor belongs to
    Picture* mPicture = nullptr;

    /// The animation channel for animating the position of this Actor
    AnimChannelPos mChannel;

public:
    /// Default constructor (disabled)
    Actor() = delete;
    
    /// Copy constructor (disabled)
    Actor(const Actor &) = delete;
    
    /// Assignment operator
    void operator=(const Actor &) = delete;

    /// Virtual destructor
    virtual ~Actor() {}

    /// New constructor
    Actor(const std::wstring &name);



    void SetPicture(Picture* picture);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    std::shared_ptr<Drawable> HitTest(wxPoint pos);

    void AddDrawable(std::shared_ptr<Drawable> drawable);

    void SetRoot(std::shared_ptr<Drawable> root);

    void SetKeyframe();

    void GetKeyframe();



    /**
     * Get the name
     * @return Name of Actor
     */
    std::wstring GetName() const { return mName; }

    /**
     * Set the position
     * @param position Position to set
     */
    void SetPosition(wxPoint position) { mPosition = position; }

    /**
     * Get the position
     * @return Position of the Actor
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * Set enabled status
     * @param enabled Status to set
     */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * Get the enabled status
     * @return True if enabled
     */
    bool IsEnabled() const { return mEnabled; }

    /**
     * Set clickable status
     * @param clickable Status to set
     */
    void SetClickable(bool clickable) { mClickable = clickable; }

    /**
     * Get the clickable status
     * @return Clickable status of Actor
     */
    bool GetClickable() const { return mClickable; }

    /**
     * Get the Picture
     * @return Picture the Actor is in
     */
    Picture* GetPicture() { return mPicture; }

    /**
     * Get the animation position channel
     * @return Animation position channel
     */
    AnimChannelPos* GetPositionChannel() { return &mChannel; }

};

#endif //CANADIANEXPERIENCE_ACTOR_H
