/**
 * @file AquariumView.h
 * @author Yeji Lee
 *
 * Declaration of the AquariumView class.
 *
 * Responsible for managing and rendering the aquarium view within the application.
 */
 
#ifndef AQUARIUMVIEW_H
#define AQUARIUMVIEW_H

#include <wx/wx.h> // Include wxWidgets
#include "Aquarium.h"
#include <algorithm>
#include "MainFrame.h"


/**
 * @class AquariumView
 *
 * View class for displaying the aquarium.
 *
 * Handles the drawing and interaction of the aquarium in the application window.
 *
 * Manages the paint events and contains an instance of the Aquarium class for rendering.
 */
class AquariumView : public wxWindow {
private:

 void OnPaint(wxPaintEvent& event);


 void OnAddFishBetaFish(wxCommandEvent& event);


 void OnAddFishNemoFish(wxCommandEvent& event);


 void OnAddFishDoryFish(wxCommandEvent& event);
 void OnAddDecorCastle(wxCommandEvent& event);

public:

 void Initialize(wxFrame* parent);


 void OnLeftDown(wxMouseEvent &event);


 void OnLeftUp(wxMouseEvent &event);


 void OnMouseMove(wxMouseEvent &event);

 /// item being moved with the mouse
 std::shared_ptr<Item> mGrabbedItem;

private:
 /// An object that describes our aquarium
 Aquarium mAquarium;

 void OnFileSaveAs(wxCommandEvent& event);
 void OnFileOpen(wxCommandEvent& event);
 void OnTimer(wxTimerEvent& event);

 /// The timer that allows for animation
 wxTimer mTimer;

 /// Stopwatch used to measure elapsed time
 wxStopWatch mStopWatch;

 /// The last stopwatch time
 long mTime = 0;
};



#endif //AQUARIUMVIEW_H
