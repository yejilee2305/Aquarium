/**
 * @file FishNemo.h
 * @author Yeji Lee
 *
 * declaration of fish nemo class
 *
 * contains declaration of fish nemo class, representing a nemo fish
 */
 
#ifndef FISHNEMO_H
#define FISHNEMO_H



#include "Fish.h"

/**
 * Class for a fish of type Nemo
 */
class FishNemo : public Fish {
private:

public:
 /// Default constructor (disabled)
 FishNemo() = delete;

 /// Copy constructor (disabled)
 FishNemo(const FishNemo &) = delete;

 /// Assignment operator
 void operator=(const FishNemo &) = delete;


 FishNemo(Aquarium* aquarium);
 wxXmlNode* XmlSave(wxXmlNode* node) override;
};



#endif //FISHNEMO_H
