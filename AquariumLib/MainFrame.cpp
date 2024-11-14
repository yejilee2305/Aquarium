/**
 * @file MainFrame.cpp
 * @author Yeji Lee
 *
 * Implementation of the MainFrame class.
 *
 * Defines the MainFrame class, which serves as the main application
 *
 * Initializes the layout and contains the aquarium view.
 */

#include "pch.h"
#include "MainFrame.h"
#include "AquariumView.h"
#include "ids.h"

/**
 * Initializes the MainFrame window.
 *
 * Sets up the main window for the aquarium application by creating the
 * main frame, setting its size, and laying out the aquarium view within it.
 */
void MainFrame::Initialize()
{
 // Create the main frame window with a title, default position, and a size of 1000x800 pixels
 Create(nullptr, wxID_ANY, L"Aquarium", wxDefaultPosition,  wxSize( 1000,800 ));

 // Create a vertical box sizer to layout child windows stacked vertically
 auto sizer = new wxBoxSizer(wxVERTICAL);

 // Create the Aquarium object as a child of MainFrame
 auto aquariumView = new AquariumView();
 aquariumView->Initialize(this);

 // Add the aquarium view to the sizer and allow it to expand
 sizer->Add(aquariumView,1, wxEXPAND | wxALL );

 // Set the sizer for this frame, allowing it to manage child window layout
 SetSizer( sizer );

 // Layout the child windows in the main frame.
 Layout();

 auto menuBar = new wxMenuBar();

 auto fileMenu = new wxMenu();

 auto helpMenu = new wxMenu();

 auto fishMenu = new wxMenu();

 menuBar->Append(fileMenu, L"&File" );
 menuBar->Append(fishMenu, L"&Add Fish");
 menuBar->Append(helpMenu, L"&Help");

 fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
 fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save aquarium as...");
 fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open aquarium file...");
 helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
 fishMenu->Append(IDM_ADDFISHBETA, L"&Beta Fish", L"Add a Beta Fish");
 fishMenu->Append(IDM_ADDFISHNEMO, L"&Nemo Fish", L"Add a Nemo Fish");
 fishMenu->Append(IDM_ADDFISHDORY, L"&Dory Fish", L"Add a Dory Fish");
 fishMenu->Append(IDM_ADDDECORCASTLE, L"&Decor Castle", L"Add a decor Castle");

 SetMenuBar( menuBar );

 Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
 Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);



 CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
}

/**
 * Exit menu option handlers
 * @param event wxCommandEvent triggered by selectring "Exit" option
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
 Close(true);
}

/**
 * shows about menu
 * @param event wxCommandEvent triggered by selecting the "About" option
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
 wxMessageBox(L"Welcome to the Aquarium!",
        L"About Aquarium",
        wxOK,
        this);
}