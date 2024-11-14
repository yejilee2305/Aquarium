/**
 * @file Fish.cpp
 * @author Yeji Lee
 */

#include "pch.h"
#include "Fish.h"
#include"Aquarium.h"
#include <random>
#include "Item.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;


Fish::Fish(Aquarium *aquarium, const std::wstring &filename) :
    Item(aquarium, filename)
{
    std::uniform_real_distribution<double> distribution(MinSpeedX, MaxSpeedX);
    mSpeedX = distribution(aquarium->GetRandom());
    mSpeedY = 0;
}


void Fish::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed, // speed of x coordinnate
            GetY() + mSpeedY * elapsed); // speed of y coordinate

    double halfWidth = mItemBitmap->GetWidth() / 2;
    double halfHeight = mItemBitmap->GetHeight() / 2;

    if (GetX() >= GetAquarium()->GetWidth() - halfWidth && mSpeedX > 0)
    {
        // If hitting the right boundary, reverse direction
        mSpeedX = -mSpeedX;
        SetMirror(true); // Mirror when changing to left direction
    }
    else if (GetX() <= halfWidth && mSpeedX < 0)
    {
        // If hitting the left boundary, reverse direction
        mSpeedX = -mSpeedX;
        SetMirror(false); // Un-mirror when changing to right direction
    }

    if (GetY() <= 10 + halfHeight || GetY() >= GetAquarium()->GetHeight() - 10 - halfHeight)
    {
        mSpeedY = -mSpeedY; // Reverse vertical direction
        // No mirroring change needed for vertical movement
    }
    static double time = 0;
    time += elapsed;

    // Change vertical direction every 1 second
    if (time > 1.0)
    {
        time = 0; // Reset the timer
        mSpeedY += (GetAquarium()->GetRandom()() % 2 == 0 ? 5 : -5);
    }
}


wxXmlNode* Fish::XmlSave(wxXmlNode* node) {
    // Save position and speed
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"speedx", wxString::Format(L"%g", mSpeedX));
    itemNode->AddAttribute(L"speedy", wxString::Format(L"%g", mSpeedY));
    return itemNode;
}

/**
 * load the fish state from an XML node
 * retrives the fish position and speed information from the node's attribute
 * @param node the XML node from which this fish data will be loaded
 */
void Fish::XmlLoad(wxXmlNode* node) {
    // Load position and speed
    Item::XmlLoad(node);
    node->GetAttribute(L"speedx").ToDouble(&mSpeedX);
    node->GetAttribute(L"speedy").ToDouble(&mSpeedY);
}


void Fish::SetRandomSpeed(double minX, double maxX, double minY, double maxY) {
    std::uniform_real_distribution<> distX(minX, maxX);
    std::uniform_real_distribution<> distY(minY, maxY);

    mSpeedX = distX(GetAquarium()->GetRandom());
    mSpeedY = distY(GetAquarium()->GetRandom());
}