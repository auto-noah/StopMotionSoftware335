/**
 * @file ImageDrawable.h
 * @author Noah Wolff
 *
 * A drawable based on images.
 */

#ifndef CANADIANEXPERIENCE_IMAGEDRAWABLE_H
#define CANADIANEXPERIENCE_IMAGEDRAWABLE_H

#include "Drawable.h"
#include "AnimChannelPos.h"


/**
 * A Drawable based on images.
 *
 * A Drawable that is an image
 */
class ImageDrawable : public Drawable {
private:
    /// Center of image
    wxPoint mCenter = wxPoint(0,0);
    
protected:
    /// The image we are drawing
    std::unique_ptr<wxImage> mImage;

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

public:
    /// Default constructor (disabled)
    ImageDrawable() = delete;

    /// New constructor
    ImageDrawable(const std::wstring &name, const std::wstring &filename);
    
    /// Copy constructor (disabled)
    ImageDrawable(const ImageDrawable &) = delete;
    
    /// Assignment operator
    void operator=(const ImageDrawable &) = delete;



    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    bool HitTest(wxPoint pos);



    /**
     * Get the center of the ImageDrawable
     * @return Center of the image
     */
    wxPoint GetCenter() { return mCenter; }

    /**
     * Set the center value of the ImageDrawable
     * @param center Center value to set
     */
    void SetCenter(wxPoint center) { mCenter = center; }

};

#endif //CANADIANEXPERIENCE_IMAGEDRAWABLE_H
