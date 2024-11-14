/**
 * @file FishDory.h
 * @author Yeji Lee
 *
 * declaration of the fishdory class
 *
 * contain declaration of the fish dory class
 *
 * represents dory fish in aquarium
 *
 * provides functionality for drawing and interaction
 */
 
#ifndef FISHDORY_H
#define FISHDORY_H



#include "Fish.h"

/**
 * Class for a fish of type Dory
 *
 * inherits from Item class
 *
 * provides functionality for drawinf and clicking dory fish
 */
class FishDory : public Fish {
private:

public:
 /// Default constructor (disabled)
 FishDory() = delete;

 /// Copy constructor (disabled)
 FishDory(const FishDory &) = delete;

 /// Assignment operator
 void operator=(const FishDory &) = delete;


 FishDory(Aquarium* aquarium);
 wxXmlNode* XmlSave(wxXmlNode* node) override;
};



#endif //FISHDORY_H
