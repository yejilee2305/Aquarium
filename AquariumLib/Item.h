/**
 * @file Item.h
 * @author Yeji Lee
 *
 * Base class for any item in our aquarium.
 *
 * Serves as the base for all objects in the Aquarium.
 *
 * Provides basic properties like position (X, Y) and manages the association with the aquarium.
 */
 
#ifndef AQUARIUM_ITEM_H
#define AQUARIUM_ITEM_H

class Aquarium;

/**
 * Base class for items in the aquarium
 */
class Item {
private:
 /// The aquarium this item is contained in
 Aquarium   *mAquarium;

 // Item location in the aquarium
 double  mX = 0;     ///< X location for the center of the item
 double  mY = 0;     ///< Y location for the center of the item


 bool mMirror = false;   ///< True mirrors the item image



protected:
 Item(Aquarium* aquarium, const std::wstring &filename);

 /// The underlying fish image

 std::unique_ptr<wxImage> mItemImage;

 /// The bitmap we can display for this fish
 std::unique_ptr<wxBitmap> mItemBitmap;

public:
 /// Default constructor (disabled)
 Item() = delete;

 /// Copy constructor (disabled)
 Item(const Item &) = delete;

 ~Item();

 /**
  * The X location of the item
  * @returns X location in pixels
  */
 double GetX() const { return mX; }

 /**
  * The Y location of the item
  * @returns Y location in pixels
  */
 double GetY() const { return mY; }

 /**
  * Set the item location
  * @param x X location in pixels
  * @param y Y location in pixels
  */
 virtual void SetLocation(double x, double y) { mX = x; mY = y; }

 virtual void Draw(wxDC *dc);

 virtual bool HitTest(int x, int y);
 virtual wxXmlNode* XmlSave(wxXmlNode* node);
 void XmlLoad(wxXmlNode* node);
 void SetMirror(bool m);

 /**
  * update function
  * @param elapsed the time
  */
 virtual void Update(double elapsed){}


 /**
  * Get the pointer to the Aquarium object
  * @return Pointer to Aquarium object
  */
 Aquarium *GetAquarium() { return mAquarium;  }

};

#endif //AQUARIUM_ITEM_H