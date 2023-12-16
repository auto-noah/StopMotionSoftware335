/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 * @author Noah Wolff
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>
#include "ViewTimeline.h"
#include "TimelineDlg.h"
#include "Picture.h"
#include "Actor.h"

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";


/**
 * Constructor
 * @param parent The main wxFrame object
 * @param imagesDir The images directory
 * @param timeline The timeline we're viewing
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring imagesDir, Timeline* timeline) :
        wxScrolledCanvas(parent,                          // Parent class
                wxID_ANY,                     // Id (don't care)
                wxDefaultPosition,           // Use the default position
                wxSize(100, Height), // Set the height to 90 pixels
                                                  // We don't care about the width
                wxBORDER_SIMPLE)            // Draw a border around the view
{
    mImagesDir = imagesDir;
    mTimeline = timeline;

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind mouse and paint events to window
    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);

    // Bind timeline edit events to the parent frame
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditSet, this, XRCID("EditSet"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditDelete, this, XRCID("EditDelete"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnEditTimelineProperties, this,
            XRCID("EditTimelineProperties"));
}

/**
 * Handle the Edit>Set Keyframe menu event
 * @param event Command event
 */
void ViewTimeline::OnEditSet(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * Handle the Edit>Delete Keyframe menu event
 * @param event Command event
 */
void ViewTimeline::OnEditDelete(wxCommandEvent& event)
{

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));


    //
    // Make the window scrollable
    //
    SetVirtualSize((mTimeline->GetNumFrames() * TickSpacing) + BorderLeft + BorderRight,
                   GetPicture()->GetSize().GetHeight());
    SetScrollRate(1, 0);


    //
    // Draw the timeline ticks
    //
    wxPen pen(wxColour(0, 0, 0), 1);
    graphics->SetPen(pen);
    wxFont font(wxSize(0, 16),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);

    int x = BorderLeft;
    for (int i = 0; i < mTimeline->GetNumFrames(); i++)
    {
        bool onSecond = (i % mTimeline->GetFrameRate()) == 0;
        if (onSecond) //< If the line is on a second
        {
            graphics->StrokeLine(x, TickTop, x, TickLong + TickTop);

            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << i / mTimeline->GetFrameRate();
            std::wstring wstr = str.str();

            double w, h;
            graphics->GetTextExtent(wstr, &w, &h);
            graphics->DrawText(wstr, x - (w / 2), TickFontSize + (h * 1.5));
        }
        else //< If the line is not a second
        {
            graphics->StrokeLine(x, TickTop, x, TickShort + TickTop);
        }

        x += TickSpacing;
    }

    mPointerImage = std::make_unique<wxImage>(mImagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);
    mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);

    graphics->DrawBitmap(mPointerBitmap,
            mTimeline->GetPointerLoc().x - (mPointerImage->GetWidth() / 2), mTimeline->GetPointerLoc().y,
            mPointerImage->GetWidth(),
            mPointerImage->GetHeight());
}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    int pointerX = (int)(mTimeline->GetCurrentTime() *
            mTimeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    if (mMovingPointer && event.LeftIsDown())
    {
        auto time = (double)(click.x - BorderLeft) / (mTimeline->GetFrameRate() * TickSpacing);
        if (time >= 0 && time <= mTimeline->GetDuration())
        {
            GetPicture()->SetAnimationTime(time);
        }
    }
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Timeline settings
        GetPicture()->UpdateObservers();
    }
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
}
