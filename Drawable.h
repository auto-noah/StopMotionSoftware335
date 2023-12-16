/**
 * @file Drawable.h
 * @author Noah Wolff
 *
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */

#ifndef CANADIANEXPERIENCE_DRAWABLE_H
#define CANADIANEXPERIENCE_DRAWABLE_H

#include "AnimChannelAngle.h"
class Actor;


/**
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */
class Drawable {
private:
    /// Name of Drawable
    std::wstring mName;

    /// X, Y position
    wxPoint mPosition = wxPoint(0, 0);

    /// Rotation
    double mRotation = 0;

    /// The Actor using this Drawable
    Actor* mActor = nullptr;

    /// The parent Drawable
    Drawable* mParent = nullptr;

    /// The children Drawables
    std::vector<std::shared_ptr<Drawable>> mChildren;

    /// The animation channel for animating the angle of this drawable
    AnimChannelAngle mChannel;

protected:
    /// The actual postion in the drawing
    wxPoint mPlacedPosition = wxPoint(0, 0);

    /// The actual rotation in the drawing
    double mPlacedRotation = 0;

    /// Constructor
    Drawable(const std::wstring &name);

    wxPoint RotatePoint(wxPoint point, double angle);

public:
    /// Default constructor (disabled)
    Drawable() = delete;

    /// Copy constructor (disabled)
    Drawable(const Drawable &) = delete;

    /// Assignment operator
    void operator=(const Drawable &) = delete;

    /// Virtual destructor
    virtual ~Drawable() {}



    void SetActor(Actor* actor);

    virtual void SetTimeline(Timeline *timeline);

    void AddChild(std::shared_ptr<Drawable> child);

    void Place(wxPoint offset, double rotate);

    void Move(wxPoint delta);

    void SetKeyframe();

    void GetKeyframe();

    /**
     * Draw this drawable
     * @param graphics Graphics object to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Test to see if we have been clicked on by the mouse
     * @param pos Position to test
     * @return true if clicked on
     */
    virtual bool HitTest(wxPoint pos) = 0;



    /**
     * Is this a movable drawable?
     * @return true if movable
     */
    virtual bool IsMovable() { return false; }

    /**
     * Get the name
     * @return Name of Drawable
     */
    std::wstring GetName() const { return mName; }

    /**
     * Set the position
     * @param position Position value to set
     */
    void SetPosition(wxPoint position) { mPosition = position; }

    /**
     * Get the position
     * @return Position of the Drawable
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * Set the rotation
     * @param rotation Rotation value to set
     */
    void SetRotation(double rotation) { mRotation = rotation; }

    /**
     * Get the rotation
     * @return Rotation value of Drawable
     */
    double GetRotation() { return mRotation; }

    /**
     * Set the child's parent Drawable
     * @param parent The parent Drawable
     */
    void SetParent(Drawable* parent) { mParent = parent; }

    /**
     * Get the parent Drawable
     * @return The child's parent Drawable
     */
    Drawable* GetParent() { return mParent; }

    /**
     * The angle animation channel
     * @return Pointer to animation channel
     */
    AnimChannelAngle *GetAngleChannel() { return &mChannel; }

};

#endif //CANADIANEXPERIENCE_DRAWABLE_H
