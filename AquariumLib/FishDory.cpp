/**
 * @file FishDory.cpp
 * @author Yeji Lee
 *
 * implementation of the fish dory class
 *
 * implement fish dory class
 *
 * represents a dory fish in aquarium
 *
 * provides methods for rendering fish and event handler
 */

#include "pch.h"
#include "FishDory.h"
#include "Aquarium.h"

using namespace std;

/// Fish filename
const wstring FishDoryImageName = L"images/dory.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishDory::FishDory(Aquarium *aquarium) : Fish(aquarium, FishDoryImageName)
{
 SetRandomSpeed(150.0, 200.0, 150.0, 200.0);
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishDory::XmlSave(wxXmlNode* node)
{
 auto itemNode = Fish::XmlSave(node);

 itemNode->AddAttribute(L"type", L"dory");

 return itemNode;


}