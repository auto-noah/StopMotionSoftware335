/**
 * @file TimelineDlg.h
 * @author Noah Wolff
 *
 * Timeline dialog box
 */

#ifndef CANADIANEXPERIENCE_TIMELINEDLG_H
#define CANADIANEXPERIENCE_TIMELINEDLG_H

class Timeline;


/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:
    /// The Timeline
    Timeline* mTimeline = nullptr;

    /// Number of frames in the animation
    int mNumberOfFrames = 0;

    /// Frame rate of animation
    int mFrmRate = 0;

public:
    /// Default constructor (disabled)
    TimelineDlg() = delete;

    /// Copy constructor (disabled)
    TimelineDlg(const TimelineDlg &) = delete;

    /// Assignment operator
    void operator=(const TimelineDlg &) = delete;

    TimelineDlg(wxWindow* parent, Timeline* timeline);

    void OnOK(wxCommandEvent& event);

};

#endif //CANADIANEXPERIENCE_TIMELINEDLG_H
