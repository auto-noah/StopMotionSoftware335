/**
 * @file PolyDrawable.h
 * @author Noah Wolff
 *
 * A drawable based on polygon images.
 */

#ifndef CANADIANEXPERIENCE_POLYDRAWABLE_H
#define CANADIANEXPERIENCE_POLYDRAWABLE_H

#include "Drawable.h"
#include <vector>


/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class PolyDrawable : public Drawable {
private:
    /// The polygon color
    wxColour mColor = *wxBLACK;

    /// The vector of point objects
    std::vector<wxPoint> mPoints;

    /// The transformed graphics path used
    /// to draw this polygon
    wxGraphicsPath mPath;

public:
    /// Default constructor (disabled)
    PolyDrawable() = delete;

    /// Copy constructor (disabled)
    PolyDrawable(const PolyDrawable &) = delete;

    /// Assignment operator
    void operator=(const PolyDrawable &) = delete;

    /// New constructor
    PolyDrawable(const std::wstring &name);



    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;

    void AddPoint(wxPoint point);



    /**
     * Get the colour
     * @return Color of the Polygon
     */
    wxColour GetColor() { return mColor; }

    /**
     * Set the color
     * @param color Color to set
     */
    void SetColor(wxColour color) { mColor = color; }

};

#endif //CANADIANEXPERIENCE_POLYDRAWABLE_H
