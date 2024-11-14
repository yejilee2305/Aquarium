/**
 * @file FishBeta.h
 * @author Yeji Lee
 *
 * declaration of fishbeta class
 *
 * contains declaration of class fishbeta, representing beta fish.
 *
 * handles drawinf and interaction of the beta fish
 */
 
#ifndef AQUARIUM_FISHBETA_H
#define AQUARIUM_FISHBETA_H

#include "Fish.h"

/**
 * FishBeta
 *
 * class representing beta fish
 *
 * inherit from Item class
 *
 * provides functionality for drawing and hit test (click)a beta fish
 */
class FishBeta : public Fish {
private:

public:
 /// Default constructor (disabled)
 FishBeta() = delete;

 /// Copy constructor (disabled)
 FishBeta(const FishBeta &) = delete;

 /// Assignment operator
 void operator=(const FishBeta &) = delete;

 /// for fish beta
 FishBeta(Aquarium* aquarium);
 wxXmlNode* XmlSave(wxXmlNode* node) override;
 /**
  * 
  * @param node node for xml
  */
 void XmlLoad(wxXmlNode* node);
};

#endif //AQUARIUM_FISHBETA_H