/**
* @file AquariumApp.h
 * @author Yeji Lee
 *
 * Declaration of the main application class for the aquarium.
 *
 * Contains the definition of the AquariumApp class, which serves as the main entry point
 * for the aquarium application.
 */

#ifndef AQUARIUM_AQUARIUMAPP_H
#define AQUARIUM_AQUARIUMAPP_H

#include <wx/wx.h>

/**
 * @class AquariumApp
 *
 * Handles the initialization of the aquarium application and the creation of the main window
 */
class AquariumApp : public wxApp {
public:
 /**
  * Initializes the application
  *
  * Called at the start of the application and is responsible for setting up the main window.
  * @return true if the initialization is successful, otherwise false.
  */
 bool OnInit() override;

};

#endif //AQUARIUM_AQUARIUMAPP_H


