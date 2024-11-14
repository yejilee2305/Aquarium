/**
 * @file ids.h
 * @author Yeji Lee
 *
 * ID values for our program.
 *
 * contains unique ID values for menu and event handling
 *
 * IDs used ti differentiate between various commands done to fish
 */
 
#ifndef AQUARIUM_IDS_H
#define AQUARIUM_IDS_H

/**
 * enum IDs
 *
 * enumeration of unique IDs for menu and event handling
 *
 * enumeration provides unique values for each command, such as adding different fish to the aquarium.
 *
 * IDs are based on wxWidget's highest ID value to avoid conflict
 */
enum IDs {
 IDM_ADDFISHBETA = wxID_HIGHEST + 1, // beta fish
 IDM_ADDFISHNEMO = wxID_HIGHEST + 2, // nemo fish
 IDM_ADDFISHDORY = wxID_HIGHEST + 3, // dory fish
 IDM_ADDDECORCASTLE = wxID_HIGHEST + 4, // Decor Castle
 IDM_ADDFISHANGEL, // angel fish
 IDM_ADDFISHCARP // carp fish
};



#endif //AQUARIUM_IDS_H