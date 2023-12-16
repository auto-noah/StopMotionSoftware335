/**
 * @file LindaFactory.cpp
 * @author Noah Wolff
 */

#include "pch.h"
#include "LindaFactory.h"
#include "Actor.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"


/**
 * This is a factory method that creates our Linda actor.
 * @param imagesDir Directory that contains the images for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> LindaFactory::Create(std::wstring imagesDir)
{
    std::shared_ptr<Actor> actor = std::make_shared<Actor>(L"Linda");

    auto coat = std::make_shared<ImageDrawable>(L"Coat", imagesDir + L"/black_coat.png");
    coat->SetCenter(wxPoint(44, 138));
    coat->SetPosition(wxPoint(0, -114));
    actor->SetRoot(coat);

    auto lleg = std::make_shared<ImageDrawable>(L"Left Leg", imagesDir + L"/jeans_lleg.png");
    lleg->SetCenter(wxPoint(21, 9));
    lleg->SetPosition(wxPoint(27, 0));
    coat->AddChild(lleg);

    auto rleg = std::make_shared<ImageDrawable>(L"Right Leg", imagesDir + L"/jeans_rleg.png");
    rleg->SetCenter(wxPoint(34, 9));
    rleg->SetPosition(wxPoint(-27, 0));
    coat->AddChild(rleg);

    auto headb = std::make_shared<ImageDrawable>(L"Head Bottom", imagesDir + L"/headb3.png");
    headb->SetCenter(wxPoint(44, 31));
    headb->SetPosition(wxPoint(0, -130));
    coat->AddChild(headb);

    auto headt = std::make_shared<HeadTop>(L"Head Top", imagesDir + L"/headt4.png");
    headt->SetEyeCenter(wxPoint(75,85));
    headt->SetCenter(wxPoint(75, 112));
    headt->SetPosition(wxPoint(0, -31));
    headb->AddChild(headt);

    auto larm = std::make_shared<PolyDrawable>(L"Left Arm");
    larm->SetColor(wxColour(0, 0, 0));
    larm->SetPosition(wxPoint(50, -130));
    larm->AddPoint(wxPoint(-7, -7));
    larm->AddPoint(wxPoint(-7, 96));
    larm->AddPoint(wxPoint(8, 96));
    larm->AddPoint(wxPoint(8, -7));
    coat->AddChild(larm);

    auto rarm = std::make_shared<PolyDrawable>(L"Right Arm");
    rarm->SetColor(wxColour(0, 0, 0));
    rarm->SetPosition(wxPoint(-45, -130));
    rarm->AddPoint(wxPoint(-7, -7));
    rarm->AddPoint(wxPoint(-7, 96));
    rarm->AddPoint(wxPoint(8, 96));
    rarm->AddPoint(wxPoint(8, -7));
    coat->AddChild(rarm);

    // Need to find correct color for hands
    auto lhand = std::make_shared<PolyDrawable>(L"Left Hand");
    lhand->SetColor(wxColour(208,159,116));
    lhand->SetPosition(wxPoint(0, 96));
    lhand->AddPoint(wxPoint(-12, -2));
    lhand->AddPoint(wxPoint(-12, 17));
    lhand->AddPoint(wxPoint(11, 17));
    lhand->AddPoint(wxPoint(11, -2));
    larm->AddChild(lhand);

    auto rhand = std::make_shared<PolyDrawable>(L"Right Hand");
    rhand->SetColor(wxColour(208,159,116));
    rhand->SetPosition(wxPoint(0, 96));
    rhand->AddPoint(wxPoint(-12, -2));
    rhand->AddPoint(wxPoint(-12, 17));
    rhand->AddPoint(wxPoint(11, 17));
    rhand->AddPoint(wxPoint(11, -2));
    rarm->AddChild(rhand);

    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(rhand);
    actor->AddDrawable(lhand);
    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(coat);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);

    return actor;
}
