/**
 * @file TimelineDlg.cpp
 * @author Noah Wolff
 */

#include "pch.h"
#include "TimelineDlg.h"
#include "Timeline.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>


/**
 * Constructor
 * @param parent The parent window we will center in
 * @param timeline Pointer to the timeline we are editing
 */
TimelineDlg::TimelineDlg(wxWindow* parent, Timeline* timeline) : mTimeline(timeline)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"TimelineDlg");

    mNumberOfFrames = timeline->GetNumFrames();
    auto numFramesCtrl = XRCCTRL(*this, "TimelineDlgNumFrames", wxTextCtrl);
    wxIntegerValidator<int> numFramesValidator(&mNumberOfFrames);
    numFramesValidator.SetRange(1, 10000);
    numFramesCtrl->SetValidator(numFramesValidator);

    mFrmRate = timeline->GetFrameRate();
    auto frameRateCtrl = XRCCTRL(*this, "TimelineDlgFrameRate", wxTextCtrl);
    wxIntegerValidator<int> frameRateValidator(&mFrmRate);
    frameRateValidator.SetRange(1, 60);
    frameRateCtrl->SetValidator(frameRateValidator);

    Bind(wxEVT_BUTTON, &TimelineDlg::OnOK, this, wxID_OK);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void TimelineDlg::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        mTimeline->SetNumFrames(mNumberOfFrames);
        mTimeline->SetFrameRate(mFrmRate);

        EndModal(wxID_OK);
    }
}
