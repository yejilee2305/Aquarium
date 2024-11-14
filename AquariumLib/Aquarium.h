/**
 * @file Aquarium.h
 * @author Yeji Lee
 *
 * Declaration of the Aquarium class.
 *
 * Responsible for managing the aquarium background and rendering it along
 * with other graphical elements.
 */
 
#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <memory> // To use unique_ptr
#include <random>
#include "Item.h"

// declaration of the class Item
class Item;

/**
 * @class Aquarium
 *
 * Manages the aquarium background and rendering.
 *
 * The Aquarium class handles the drawing of the aquarium background and displays
 * additional graphics or texts.
 */
class Aquarium
{
private:
 /// background image
 std::unique_ptr<wxBitmap> mBackground;

 /// All of the items to populate our aquarium
 std::vector<std::shared_ptr<Item>> mItems;

 void XmlItem(wxXmlNode* node);
 //void Update(double elapsed);

 /// Random number generator
 std::mt19937 mRandom;

public:
 /**
 * Constructor for Aquarium.
 *
 * Initializes the aquarium by loading the background image.
 */
 Aquarium(); // Constructor declaration


 void OnDraw(wxDC* dc);


 void Add(std::shared_ptr<Item> item);


 std::shared_ptr<Item> HitTest(int x, int y);


 void MoveToFront(std::shared_ptr<Item> item);

 /**
  * return list of items
  *
  * access to the vector of items in aquarium
  *
  * item are stored as shared pointer in Item
  *
  * @return const reference to the vector of shared pointer
  */
 const std::vector<std::shared_ptr<Item>>& GetFishes() const {return mItems;}

 void Save(const wxString &filename);
 void Load(const wxString& filename);
 void Clear(const wxString& filename);

 void Update(double elapsed);

 /**
    * Get the random number generator
    * @return Reference to the random number generator
    */
 std::mt19937 &GetRandom() { return mRandom; }

 /**
* Get the width of the aquarium
* @return Aquarium width in pixels
*/
 int GetWidth() const { return mBackground->GetWidth(); }

 /**
  * Get the height of the aquarium
  * @return Aquarium height in pixels
  */
 int GetHeight() const { return mBackground->GetHeight(); }
};
#endif //AQUARIUM_H
