/**
 * @file Aquarium.cpp
 * @author Yeji Lee
 * Implementation of the Aquarium class.
 *
 * Implements the Aquarium class, responsible for drawing the
 * aquarium background and text
 */

#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "FishNemo.h"
#include "FishDory.h"
#include <algorithm>
#include "DecorCastle.h"
#include "Item.h"

using namespace std;

/// initial x - coordinate for recently added item
const int InitialX = 200;
/// initial y - coordinate for recently added item
const int InitialY = 200; // initial y - coordinate for recently added item

/**
 * Aquarium Constructor
 *
 * initialize Aquarium background image (given)
 */
Aquarium::Aquarium()
{
 random_device rd;
 mRandom.seed(rd());
 // image from the folder "images"
 mBackground = make_unique<wxBitmap>(
         L"images/background1.png", wxBITMAP_TYPE_ANY);
}

/**
 * Draws the aquarium background and text.
 *
 * Responsible for rendering the background image of the aquarium
 * and displaying a title text at the top of the window.
 *
 * @param dc The device contact to draw on.
 */
void Aquarium::OnDraw(wxDC *dc)
{
 // setting image at (0,0) location
 dc->DrawBitmap(*mBackground, 0, 0);

 // font for title "Under the Sea!"
 wxFont font(wxSize(0, 20),
         wxFONTFAMILY_SWISS,
         wxFONTSTYLE_NORMAL,
         wxFONTWEIGHT_NORMAL);
 dc->SetFont(font);
 // color = MSU green
 dc->SetTextForeground(wxColour(0, 64, 0));
 // text quotes
 dc->DrawText(L"Under the Sea!", 10, 10);

 // iterating each item in Aquarium
 for (auto item : mItems)
 {
  // draw current item
  item->Draw(dc);
 }
}

/**
 * Add an item to the aquarium
 *
 * @param item New item to add
 */
void Aquarium::Add(std::shared_ptr<Item> item)
{
 // setting initial location of recent item
 item->SetLocation(InitialX, InitialY);

 // adding item to the list
 mItems.push_back(item);

 // error check for debug
 std::cout << "Item added at " << item->GetX() << ", " << item->GetY() <<std::endl;
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Aquarium::HitTest(int x, int y)
{
 // reversing iteration
 for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
 {
  // if clicked,
  if ((*i)->HitTest(x, y))
  {
   // return
   return *i;
  }
 }
// if not clicked, return nullptr
 return  nullptr;
}

/**
 * moves item to the front
 *
 * making sure given item will be drawn on top
 *
 * @param item A pointer to the item to move front
 */
void Aquarium::MoveToFront(std::shared_ptr<Item> item)
{
 // find item
 auto loc = std::find(mItems.begin(), mItems.end(), item);

 // if item found
 if (loc != end(mItems))
 {
  // remove from current location
  mItems.erase(loc);
  // read item to the back
  mItems.push_back(item);
 }
}

/**
* Save the aquarium as a .aqua XML file.
*
* Open an XML file and stream the aquarium data to it.
*
* @param filename The filename of the file to save the aquarium to
*/
void Aquarium::Save(const wxString &filename)
{
 wxXmlDocument xmlDoc;

 auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
 xmlDoc.SetRoot(root);

 // Iterate over all items and save them
 for (auto item : mItems)
 {
  item->XmlSave(root);
 }


 if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
 {
  wxMessageBox(L"Write to XML failed");
  return;
 }
}
/**
 * Load the aquarium from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the aquarium from.
 */

void Aquarium::Load(const wxString &filename)
{
 wxXmlDocument xmlDoc;
 if(!xmlDoc.Load(filename))
 {
  wxMessageBox(L"Unable to load Aquarium file");
  return;
 }

 Clear(filename);

 // Get the XML document root node
 auto root = xmlDoc.GetRoot();

 //
 // Traverse the children of the root
 // node of the XML document in memory!!!!
 //
 auto child = root->GetChildren();
 for( ; child; child=child->GetNext())
 {
  auto name = child->GetName();
  if(name == L"item")
  {
   XmlItem(child);
  }
 }

}


/**
 * 
 * @param filename reference file
 */
void Aquarium::Clear(const wxString &filename)
{
 mItems.clear();
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Aquarium::XmlItem(wxXmlNode *node)
{
 // A pointer for the item we are loading
 shared_ptr<Item> item;

 // We have an item. What type?
 auto type = node->GetAttribute(L"type");
 if (type == L"beta")
 {
  item = make_shared<FishBeta>(this);
 }

 if (type == L"castle")
 {
  item = make_shared<DecorCastle>(this);
 }

 if (type == L"nemo")
 {
  item = make_shared<FishNemo>(this);
 }

 if (type == L"dory")
 {
  item = make_shared<FishDory>(this);
 }

 if (item != nullptr)
 {

  Add(item);

  item->XmlLoad(node);
 }
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Aquarium::Update(double elapsed)
{
 for (auto item : mItems)
 {
  item->Update(elapsed);
 }
}






