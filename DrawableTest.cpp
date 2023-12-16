/**
 * @file DrawableTest.cpp
 * @author Noah Wolff
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Drawable.h>
#include <Picture.h>
#include <PolyDrawable.h>
#include <Actor.h>
using namespace std;

class DrawableMock : public Drawable
{
public:
    DrawableMock(const std::wstring &name) : Drawable(name) {}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}

    virtual bool HitTest(wxPoint pos) override { return false; }
};

TEST(DrawableTest, Construct) {
    DrawableMock drawable(L"Jimbo");
}

TEST(DrawableTest, NameGetter) {
    // Construct a Drawable with a name
    DrawableMock drawable(L"Jimbo");

    // Make sure the name is correct
    ASSERT_EQ(drawable.GetName(), std::wstring(L"Jimbo"));
}

TEST(DrawableTest, PosGetterSetter) {
    // Construct a Drawable with a name
    DrawableMock drawable(L"Jimbo");

    // Make sure the default pos is correct
    ASSERT_EQ(drawable.GetPosition(), wxPoint(0, 0));

    // Set new position
    drawable.SetPosition(wxPoint(6, 9));

    // Test for new position
    ASSERT_EQ(drawable.GetPosition(), wxPoint(6, 9));
}

TEST(DrawableTest, RotGetterSetter) {
    // Construct a Drawable with a name
    DrawableMock drawable(L"Jimbo");

    // Make sure the default rotation is correct
    ASSERT_NEAR(drawable.GetRotation(), 0, 0.00001);

    // Set new rotation
    drawable.SetRotation(69.420);

    // Test for new rotation
    ASSERT_NEAR(drawable.GetRotation(), 69.420, 0.00001);
}

TEST(DrawableTest, Association)
{
    DrawableMock body(L"Body");
    auto arm = std::make_shared<DrawableMock>(L"Arm");
    auto leg = std::make_shared<DrawableMock>(L"Leg");

    ASSERT_EQ(nullptr, arm->GetParent());
    ASSERT_EQ(nullptr, leg->GetParent());

    body.AddChild(arm);
    body.AddChild(leg);

    ASSERT_EQ(&body, arm->GetParent());
    ASSERT_EQ(&body, leg->GetParent());
}

TEST(ActorTest, SetPicture)
{
    // Create a picture object
    auto picture = std::make_shared<Picture>();

    // Create an actor and add it to the picture
    auto actor = std::make_shared<Actor>(L"Actor");

    // Create a drawable for the actor
    auto drawable = std::make_shared<PolyDrawable>(L"Drawable");
    actor->SetRoot(drawable);
    actor->AddDrawable(drawable);

    picture->AddActor(actor);

    auto channel = drawable->GetAngleChannel();
    ASSERT_EQ(channel->GetTimeline(), picture->GetTimeline());
}
