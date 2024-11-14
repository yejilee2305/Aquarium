/**
 * @file DecorCastle.h
 * @author Yeji Lee
 *
 *
 */
 
#ifndef DECORCASTLE_H
#define DECORCASTLE_H

#include "Item.h"

/**
 * DecorCastle
 *
 * class representing beta fish
 *
 * inherit from Item class
 *
 * provides functionality for drawing and hit test (click)a beta fish
 */
class DecorCastle : public Item {
private:

public:
 /// Default constructor (disabled)
 DecorCastle() = delete;

 /// Copy constructor (disabled)
 DecorCastle(const DecorCastle &) = delete;

 /// Assignment operator
 void operator=(const DecorCastle &) = delete;

 /// for fish beta
 DecorCastle(Aquarium* aquarium);
 wxXmlNode* XmlSave(wxXmlNode* node) override;
};

#endif //DECORCASTLE_H
