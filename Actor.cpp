/**
 * @file Actor.cpp
 * @author Noah Wolff
 */

#include "pch.h"
#include "Actor.h"
#include "Drawable.h"
#include "Picture.h"
#include <vector>

/**
 * Constructor
 * @param name Name for Actor
 */
Actor::Actor(const std::wstring &name) : mName(name)
{
}

/**
 * Set the Picture
 * @param picture Picture the Actor is in
 */
void Actor::SetPicture(Picture* picture)
{
    mPicture = picture;

    // Set the channel name
    mPicture->GetTimeline()->AddChannel(&mChannel);

    // Set the timeline for all drawables. This links the channels to
    // the timeline system.
    for (auto drawable : mDrawablesInOrder)
    {
        drawable->SetTimeline(mPicture->GetTimeline());
    }
}

/**
 * Draw this Actor on a device context
 * @param graphics The device context to draw on
 */
void Actor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Don't draw if not enabled
    if (!mEnabled)
        return;

    // This takes care of determining the absolute placement
    // of all the child drawables. We have to determine this
    // in tree order, which may not be the order we draw.
    if (mRoot != nullptr)
        mRoot->Place(mPosition, 0);

    // Draw
    for (auto drawable : mDrawablesInOrder)
    {
        drawable->Draw(graphics);
    }
}

/**
 * Test to see if a mouse click is on this actor.
 * @param pos Mouse position on drawing
 * @return A drawable object we clicked on or nullptr if we missed.
 */
std::shared_ptr<Drawable> Actor::HitTest(wxPoint pos)
{
    // If not enabled or not clickable, we indicate no hit.
    if (!mClickable || !mEnabled)
        return nullptr;

    // Since this list is in drawing order, we realy want to know the last thing drawn
    // under the mouse, since it will be on top. So, we reverse iterate over the list.
    for (auto d = mDrawablesInOrder.rbegin(); d != mDrawablesInOrder.rend(); d++)
    {
        auto drawable = *d;
        if (drawable->HitTest(pos))
            return drawable;
    }

    return nullptr;
}

/**
 * Set the root drawable for the actor
 * @param root Pointer to root drawable
 */
void Actor::SetRoot(std::shared_ptr<Drawable> root)
{
    mRoot = root;
}

/**
* Add a drawable to this actor
* @param drawable The drawable to add
*/
void Actor::AddDrawable(std::shared_ptr<Drawable> drawable)
{
    mDrawablesInOrder.push_back(drawable);
    drawable->SetActor(this);
}

/**
 * Set a keyframe on an actor.
 */
void Actor::SetKeyframe()
{
    mChannel.SetKeyframe(mPosition);

    for (auto drawable : mDrawablesInOrder)
    {
        drawable->SetKeyframe();
    }
}

/**
 * Get a keyframe for an actor.
 */
void Actor::GetKeyframe()
{
    if (mChannel.IsValid())
        mPosition = mChannel.GetPosition();

    for (auto drawable : mDrawablesInOrder)
    {
        drawable->GetKeyframe();
    }
}
