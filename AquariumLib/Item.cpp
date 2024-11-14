/**
 * @file Item.cpp
 * @author Yeji Lee
 *
 * Implementation of the Item class.
 *
 * Defines the constructor and destructor for the Item class,
 * which represents a base class for objects in the aquarium.
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"
#include <wx/xml/xml.h>

using namespace std;

/**
 * Constructor
 * @param aquarium The aquarium this item is a member of
 * @param filename The name of the file to display for this item
 */
Item::Item(Aquarium *aquarium, const std::wstring &filename) : mAquarium(aquarium)
{
 mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
 mItemBitmap = make_unique<wxBitmap>(*mItemImage);
}


/**
 * Destructor
 *
 * cleans resources associated with Item.
 *
 * destructor is empty
 */
Item::~Item()
{

}

/**
 * Draw beta fish to aquarium
 *
 * renders beta fish and fish is drawen centered
 *
 * @param dc Device context to draw on
 */
void Item::Draw(wxDC *dc)
{
 double wid = mItemBitmap->GetWidth();
 double hit = mItemBitmap->GetHeight();

 // draw fish bitmap centered at position
 dc->DrawBitmap(*mItemBitmap,
         int(GetX() - wid / 2), // x coordinate for centering fish
         int(GetY() - hit / 2)); // y coordinate for centering fish
}

/**
 * Test to see if we hit this object with a mouse.
 *
 * check if x and y coordinates fall in image and takes transparency of image
 *
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
 double wid = mItemBitmap->GetWidth(); // width of fish
 double hit = mItemBitmap->GetHeight(); // height of fish

 // Make x and y relative to the top-left corner of the bitmap image
 // Subtracting the center makes x, y relative to the image center
 // Adding half the size makes x, y relative to the image top corner
 double testX = x - GetX() + wid / 2;
 double testY = y - GetY() + hit / 2;

 // Test to see if x, y are in the image
 if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
 {

  // We are outside the image
  return false;
 }

 // Test to see if x, y are in the drawn part of the image
 // If the location is transparent, we are not in the drawn
 // part of the image
 return !mItemImage->IsTransparent((int)testX, (int)testY);

}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode *Item::XmlSave(wxXmlNode *node)
{
 auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
 node->AddChild(itemNode);

 itemNode->AddAttribute(L"x", wxString::FromDouble(mX));
 itemNode->AddAttribute(L"y", wxString::FromDouble(mY));

 return itemNode;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
 node->GetAttribute(L"x", L"0").ToDouble(&mX);
 node->GetAttribute(L"y", L"0").ToDouble(&mY);
}

/**
 * Set the mirror status
 * @param m New mirror flag
 */
void Item::SetMirror(bool m) {
 if (m != mMirror) // Only change if the state is different
 {
  mMirror = m;

  if (mMirror)
  {
   mItemBitmap = std::make_unique<wxBitmap>(mItemImage->Mirror());
  }
  else
  {
   mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
  }
 }
}