/**
 * @file AquariumView.cpp
 * @author Yeji Lee
 *
 * Implementation of the AquariumView class.
 *
 * Implements the AquariumView class, which handles rendering the aquarium view
 * in the application.
 */

# include "pch.h"
#include "AquariumView.h"
#include "FishBeta.h"
#include "MainFrame.h"
#include <wx/dcbuffer.h>
#include "ids.h"
#include "FishNemo.h"
#include "FishDory.h"
#include "DecorCastle.h"
#include "Item.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initializes the AquariumView class.
 *
 * Sets up the AquariumView as a child of the provided parent frame and binds
 * the paint event to the OnPaint method for custom drawing.
 *
 * @param parent The parent window for this class (typically a wxFrame).
 */
void AquariumView::Initialize(wxFrame* parent)
{
 // Creates the window as a child of the parent frame with a default ID
 Create(parent, wxID_ANY);

 // Set the background style to support custom painting
 SetBackgroundStyle(wxBG_STYLE_PAINT);

 // Bind the paint event to the OnPaint method for handling painting
 Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);

 // bind menu selection for event handlers
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishNemoFish, this, IDM_ADDFISHNEMO);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishDoryFish, this, IDM_ADDFISHDORY);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddDecorCastle, this, IDM_ADDDECORCASTLE);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this, wxID_SAVEAS);

 // bind mouse event
 Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
 Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
 Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
 Bind(wxEVT_TIMER, &AquariumView::OnTimer, this);

 mTimer.SetOwner(this);
 mTimer.Start(FrameDuration);

 mStopWatch.Start();
}

/**
 * Handles the paint event to draw the aquarium.
 *
 * Uses wxAutoBufferedPaintDC to avoid flickering, sets the background color to white,
 * and calls the OnDraw method of the Aquarium class to render the aquarium content.
 *
 * @param event The paint event triggered by wxWidgets.
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
 // double bufffering preventing flickering
 wxAutoBufferedPaintDC dc(this); // Use double-buffering to prevent flickering


 // Compute the time that has elapsed
 // since the last call to OnPaint.
 auto newTime = mStopWatch.Time();
 auto elapsed = (double)(newTime - mTime) * 0.001;
 mTime = newTime;

 mAquarium.Update(elapsed);

 // Sets the background color to white and clear the device context.
 wxBrush background(*wxWHITE);
 dc.SetBackground(background);
 dc.Clear();

 // Call the OnDraw method of the Aquarium class to render the aquarium content.
 mAquarium.OnDraw(&dc);
}

/**
 * Menu hander for Add Fish>Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
 auto fish = make_shared<FishBeta>(&mAquarium);
 mAquarium.Add(fish);
 Refresh();
}

/**
 * menu handler for adding nemo fish
 *
 * make new nemo fish and add to aquarium then refresh
 *
 * @param event msnu event triggered when user click add nemo fish
 */
void AquariumView::OnAddFishNemoFish(wxCommandEvent& event)
{
 auto fish = make_shared<FishNemo>(&mAquarium);
 mAquarium.Add(fish);
 Refresh();
}

/**
 * msnu handler for adding dory fish
 *
 * make new dory fish and add to aquarium then refresh
 *
 * @param event menu event triggered when user click add dory fish
 */
void AquariumView::OnAddFishDoryFish(wxCommandEvent& event)
{
 auto fish = make_shared<FishDory>(&mAquarium);
 mAquarium.Add(fish);
 Refresh();
}

/**
 * menu handler for adding dory fish
 *
 * make new dory fish and add to aquarium then refresh
 *
 * @param event menu event triggered when user click add dory fish
 */
void AquariumView::OnAddDecorCastle(wxCommandEvent& event)
{
 auto fish = make_shared<DecorCastle>(&mAquarium);
 mAquarium.Add(fish);
 Refresh();
}

/**
 * Handle the left mouse button down event
 *
 * detect if item is clicked and moved to the front and calls OnSingleClick for item
 * @param event
 */
void AquariumView::OnLeftDown(wxMouseEvent &event)
{
 // checking if the click hit any item
 mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
 if (mGrabbedItem != nullptr)
 {
  // We have selected an item
  // Move it to the end of the list of items
  mAquarium.MoveToFront(mGrabbedItem);

  // refresh to show change
  Refresh();
 }
}

/**
* Handle the left mouse button down event
*
* used to release any item that is dragged
*
* @param event the mouse event triggered by releasing mouse button
*/
void AquariumView::OnLeftUp(wxMouseEvent &event)
{
 // calling OnMouseMove to release
OnMouseMove(event);
}

/**
* Handle the left mouse button down event
*
* if item is selected, drag
*  mouse event triggered by moving mouse
* @param event mousevenet
*/
void AquariumView::OnMouseMove(wxMouseEvent &event)
{
 // See if an item is currently being moved by the mouse
 if (mGrabbedItem != nullptr){
  // If an item is being moved, we only continue to
  // move it while the left button is down.
  if (event.LeftIsDown())
  {
   mGrabbedItem->SetLocation(event.GetX(), event.GetY());
  } else {
   // When the left button is released, we release the
   // item.
   mGrabbedItem = nullptr;
  }

  // Force the screen to redraw
  Refresh();
 }
}

/**
 * save file on menu
 * @param event command event
 */
void AquariumView::OnFileSaveAs(wxCommandEvent &event)
 {
  wxFileDialog saveFileDialog(this, L"Save Aquarium file", L"", L"",
        L"Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
  if (saveFileDialog.ShowModal() == wxID_CANCEL)
  {
   return;
  }

  auto filename = saveFileDialog.GetPath();
 mAquarium.Save(filename);
 }

/**
 * File>Open menu handler
 * @param event Menu event
 */
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
 wxFileDialog loadFileDialog(this, L"Load Aquarium file", L"", L"",
         L"Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
 if (loadFileDialog.ShowModal() == wxID_CANCEL)
 {
  return;
 }

 auto filename = loadFileDialog.GetPath();
 mAquarium.Load(filename);
 Refresh();

}

/**
 * sets timer
 * @param event timer event
 */
void AquariumView::OnTimer(wxTimerEvent& event)
{
 Refresh();
}