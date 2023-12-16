/**
 * @file Drawable.cpp
 * @author Noah Wolff
 */

#include "pch.h"
#include "Drawable.h"
#include "Actor.h"
#include "Timeline.h"


/**
 * Constructor
 * @param name Name for Drawable
 */
Drawable::Drawable(const std::wstring &name) : mName(name)
{

}

/**
 * Set the Drawable's Actor
 * @param actor Actor to set
 */
void Drawable::SetActor(Actor* actor)
{
    mActor = actor;

    // Set the channel name
    mChannel.SetName(actor->GetName() + L":" + mName);
}

/**
 * Add the channels for this drawable to a timeline
 * @param timeline The timeline class.
 */
void Drawable::SetTimeline(Timeline *timeline)
{
    timeline->AddChannel(&mChannel);
}

/**
 * Add a child Drawable to a parent Drawable
 * @param child Child to add
 */
void Drawable::AddChild(std::shared_ptr<Drawable> child)
{
    mChildren.push_back(child);
    child->SetParent(this);
}

/**
 * Place this drawable relative to its parent
 *
 * This works hierarchically from top item down.
 * @param offset Parent offset
 * @param rotate Parent rotation
 */
void Drawable::Place(wxPoint offset, double rotate)
{
    // Combine the transformation we are given with the transformation
    // for this object.
    mPlacedPosition = offset + RotatePoint(mPosition, rotate);
    mPlacedRotation = mRotation + rotate;

    // Update our children
    for (auto drawable : mChildren)
    {
        drawable->Place(mPlacedPosition, mPlacedRotation);
    }
}

/**
 * Move a Drawable
 * @param delta Angle to move
 */
void Drawable::Move(wxPoint delta)
{
    if (mParent != nullptr)
    {
        mPosition = mPosition + RotatePoint(delta, -mParent->mPlacedRotation);
    }
    else
    {
        mPosition = mPosition + delta;
    }
}

/**
 * Rotate a point by a given angle.
 * @param point The point to rotate
 * @param angle An angle in radians
 * @return Rotated point
 */
wxPoint Drawable::RotatePoint(wxPoint point, double angle)
{
    double cosA = cos(angle);
    double sinA = sin(angle);

    return wxPoint(int(cosA * point.x + sinA * point.y),
            int(-sinA * point.x + cosA * point.y));
}

/**
 * Set a keyframe based on the current position.
 */
void Drawable::SetKeyframe()
{
    mChannel.SetKeyframe(mRotation);
}

/**
 * Get a keyframe update from the animation system.
 */
void Drawable::GetKeyframe()
{
    if (mChannel.IsValid())
        mRotation = mChannel.GetAngle();
}
