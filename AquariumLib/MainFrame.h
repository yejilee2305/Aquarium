/**
* @file MainFrame.h
 * @author Yeji Lee
 *
 * Declaration of the MainFrame class.
 *
 * Represents the top-level (main) frame of the aquarium application.
 *
 * Manages the main window where the aquarium view and other UI elements are displayed.
 */

#ifndef AQUARIUM_MAINFRAME_H
#define AQUARIUM_MAINFRAME_H

#include <wx/wx.h>

/**
 * @class MainFrame
 * The top-level frame of the application.
 *
 * The main window of the aquarium application.
 *
 * Initialzies the layout and handles the creation of child windows, such as the
 * Aquariumview.
 */
class MainFrame : public wxFrame {
private:

public:

 void Initialize();


 void OnExit(wxCommandEvent& event);

 void OnAbout(wxCommandEvent& event);

};

#endif //AQUARIUM_MAINFRAME_H