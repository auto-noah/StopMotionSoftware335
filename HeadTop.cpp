/**
 * @file HeadTop.cpp
 * @author Noah Wolff
 */

#include "pch.h"
#include "HeadTop.h"

/**
 * Constructor
 * @param name Name of the HeadTop
 * @param filename File
 */
HeadTop::HeadTop(const std::wstring &name, const std::wstring &filename) : ImageDrawable(name, filename)
{
}

/**
 * Transform a point from a location on the bitmap to
 * a location on the screen.
 * @param p Point to transform
 * @returns Transformed point
 */
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedRotation) + mPlacedPosition;
}

/**
 * Draws the left eyebrow
 * @param graphics Graphics Context to draw on
 */
void HeadTop::LeftEyebrow(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Left eyebrow (offset to correct pos)
    wxPoint p1 = TransformPoint(mEyeCenter + wxPoint(-25, -17));
    wxPoint p2 = TransformPoint(mEyeCenter + wxPoint(-10, -20));
    graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);
}

/**
 * Draws the right eyebrow
 * @param graphics Graphics Context to draw on
 */
void HeadTop::RightEyebrow(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Right eyebrow (offset to correct pos)
    wxPoint p1 = TransformPoint(mEyeCenter + wxPoint(10, -20));
    wxPoint p2 = TransformPoint(mEyeCenter + wxPoint(25, -17));
    graphics->StrokeLine(p1.x, p1.y, p2.x, p2.y);
}

/**
 * Draws the left eye
 * @param graphics Graphics Context to draw on
 * @param wid Width to make the eye
 * @param hit Height to make the eye
 */
void HeadTop::LeftEye(std::shared_ptr<wxGraphicsContext> graphics, float wid, float hit)
{
    wxPoint e1 = TransformPoint( mEyeCenter + wxPoint(-17, 0)); //< offset the eye to correct pos
    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedRotation);
    wxBrush brush(*wxBLACK);
    graphics->SetBrush(brush);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();
}

/**
 * Draws the right eye
 * @param graphics Graphics Context to draw on
 * @param wid Width to make the eye
 * @param hit Height to make the eye
 */
void HeadTop::RightEye(std::shared_ptr<wxGraphicsContext> graphics, float wid, float hit)
{
    wxPoint e1 = TransformPoint(mEyeCenter + wxPoint(17, 0)); //< offset the eye to correct pos
    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedRotation);
    wxBrush brush(*wxBLACK);
    graphics->SetBrush(brush);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();
}

/**
 * Draw this HeadTop
 * @param graphics Graphics object to draw on
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);
    wxPen eyebrowPen(*wxBLACK, 2);
    graphics->SetPen(eyebrowPen);

    // Draw eyebrows
    LeftEyebrow(graphics);
    RightEyebrow(graphics);

    // Draw eyes
    float wid = 15.0f;
    float hit = 20.0f;
    LeftEye(graphics, wid, hit);
    RightEye(graphics, wid, hit);
}
