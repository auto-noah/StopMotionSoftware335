/**
 * @file PictureObserver.h
 * @author Noah Wolff
 *
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */

#ifndef CANADIANEXPERIENCE_PICTUREOBSERVER_H
#define CANADIANEXPERIENCE_PICTUREOBSERVER_H

class Picture;

/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class PictureObserver {
private:
    /// Picture we are observing
    std::shared_ptr<Picture> mPicture;

protected: //< to make a class abstract, you make the constructor protected
    /// Constructor
    PictureObserver() {}

public:
    /// Copy Constructor (Disabled)
    PictureObserver(const PictureObserver &) = delete;

    /// Assignment Operator (Disabled)
    void operator=(const PictureObserver &) = delete;

    /// Virtual Destructor
    virtual ~PictureObserver();

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    /**
     * Get the picture
     * @return Shared ptr to picture
     */
    std::shared_ptr<Picture> GetPicture() { return mPicture; }

    void SetPicture(std::shared_ptr<Picture> picture);
};

#endif //CANADIANEXPERIENCE_PICTUREOBSERVER_H
