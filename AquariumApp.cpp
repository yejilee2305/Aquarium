/**
* @file AquariumApp.cpp
* @author Yeji Lee
*
* Implementation of the main application class for the aquarium.
*
* Defines the entry point for the aquarium application, where the main
* frame is created and the application is initialized.
*/

#include "pch.h"
#include "AquariumApp.h"
#include <MainFrame.h>

/**
 * @class AquariumApp
 *
 * the main application class for the aquarium.
 *
 * Handles the initialization and startup of the aquarium application.
 *
 * Initializes the aquarium application.
 *
 * Sets up the main frame, initializes image handlers, and starts the application.
 * @return true if the initialization is successful, otherwise false
 */
bool AquariumApp::OnInit()
 {
 // Call the base class OnInit to ensure proper initialization
  if (!wxApp::OnInit())
   return false;

  // Initialize all image handlers for wxWidgets
  wxInitAllImageHandlers();

 // Create and initialize the main frame of the application
  auto frame = new MainFrame();
  frame->Initialize();

 // show the main frame window.
  frame->Show(true);

 // return true to indicate successful initialization.
  return true;
 }




