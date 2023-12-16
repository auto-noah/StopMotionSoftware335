/**
 * @file MainFrame.cpp
 * @author Charles B. Owen
 * @author Noah Wolff
 */

#include "pch.h"
#include "MainFrame.h"
#include "ViewEdit.h"
#include "ViewTimeline.h"
#include "Picture.h"
#include "PictureFactory.h"
#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

/// Directory within the resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 */
MainFrame::MainFrame()
{

}

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    //
    // Create the picture
    //

    wxStandardPaths& standardPaths = wxStandardPaths::Get();
    auto imagesDir = standardPaths.GetResourcesDir().ToStdWstring() + ImagesDirectory;

    // Create our picture
    PictureFactory factory;
    mPicture = factory.Create(imagesDir);


    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");

#ifdef WIN32
    // This sets the frame icon on Windows systems
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif

    // Bind Menu Evevnt handlers
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    // Create Edit and Timeline views
    mViewEdit = new ViewEdit(this);
    mViewTimeline = new ViewTimeline(this, imagesDir, mPicture->GetTimeline());

    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Add the views to the window
    sizer->Add(mViewEdit,1, wxEXPAND | wxALL );
    sizer->Add(mViewTimeline, 0, wxEXPAND | wxALL);

    // Tell the views about the picture
    mViewEdit->SetPicture(mPicture);
    mViewTimeline->SetPicture(mPicture);

    SetSizer( sizer );
    Layout();
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Application about box menu handler
 * @param event The menu event
 */
void MainFrame::OnAbout(wxCommandEvent&event)
{
    wxDialog aboutDlg;
    wxXmlResource::Get()->LoadDialog(&aboutDlg, this, L"AboutDialog");
    aboutDlg.ShowModal();
}
