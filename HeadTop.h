/**
 * @file HeadTop.h
 * @author Noah Wolff
 *
 * Class to describe the top of an Actor's head
 */

#ifndef CANADIANEXPERIENCE_HEADTOP_H
#define CANADIANEXPERIENCE_HEADTOP_H

#include "ImageDrawable.h"


/**
 * Class to describe the top of an Actor's head
 */
class HeadTop : public ImageDrawable {
private:
    /// Center position for the eyes (default for harold)
    wxPoint mEyeCenter = wxPoint(55, 85);

public:
    /// Default constructor (disabled)
    HeadTop() = delete;

    /// New constructor
    HeadTop(const std::wstring &name, const std::wstring &filename);

    /// Copy constructor (disabled)
    HeadTop(const HeadTop &) = delete;

    /// Assignment operator
    void operator=(const HeadTop &) = delete;



    wxPoint TransformPoint(wxPoint p);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void LeftEyebrow(std::shared_ptr<wxGraphicsContext> graphics);

    void RightEyebrow(std::shared_ptr<wxGraphicsContext> graphics);

    void LeftEye(std::shared_ptr<wxGraphicsContext> graphics, float wid, float hit);

    void RightEye(std::shared_ptr<wxGraphicsContext> graphics, float wid, float hit);



    /**
     * Is this a movable drawable?
     * @return True since HeadTop
     */
    bool IsMovable() override { return true; }

    /**
     * Set the eye center value for the HeadTop
     * @param eyeCenter Eye center point value to set
     */
    void SetEyeCenter(wxPoint eyeCenter) { mEyeCenter = eyeCenter; }

};

#endif //CANADIANEXPERIENCE_HEADTOP_H
