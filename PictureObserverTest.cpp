/**
 * @file PictureObserverTest.cpp
 * @author Noah Wolff
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <PictureObserver.h>
#include <Picture.h>

using namespace std;

/**
 * PictureObserver mock class for testing
 */
class PictureObserverMock : public PictureObserver {
public:
    PictureObserverMock() : PictureObserver() {}

    virtual void UpdateObserver() override { mUpdated = true; }

    bool mUpdated = false;

};

TEST(PictureObserverTest, Construct) {
    PictureObserverMock observer;
}

TEST(PictureObserverTest, OneObserver) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);
}

TEST(PictureObserverTest, TwoObservers) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create mock observer objects
    PictureObserverMock observer1;
    PictureObserverMock observer2;

    // And set the observer to the picture:
    observer1.SetPicture(picture);
    observer2.SetPicture(picture);

    // Update observers
    picture->UpdateObservers();

    // Very the observers have been updated
    ASSERT_TRUE(observer1.mUpdated);
    ASSERT_TRUE(observer2.mUpdated);
}

TEST(PictureObserverTest, DestroyObservers) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Make an observer and set it to the picture
    PictureObserverMock observer1;
    observer1.SetPicture(picture);

    {
        // Make another observer and set it to the picture
        PictureObserverMock observer2;
        observer2.SetPicture(picture);
        //^ This observer should delete itself from the
        //  picture's mObservers vector
    }

    // Update the observer
    picture->UpdateObservers();

    // Test to make sure the mObservers vector only has one observer
    // and is updated
    ASSERT_EQ(picture->GetObservers().size(), 1);
    ASSERT_TRUE(observer1.mUpdated);
}

TEST(PictureObserverTest, GetPicture) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // Make sure the observer has no picture
    ASSERT_EQ(observer.GetPicture(), nullptr);

    // Set picture for the observer
    observer.SetPicture(picture);

    // Test to make sure the observer
    // is set to the picture
    ASSERT_EQ(observer.GetPicture(), picture);
}