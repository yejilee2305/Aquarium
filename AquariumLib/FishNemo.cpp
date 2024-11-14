/**
 * @file FishNemo.cpp
 * @author Yeji Lee
 *
 * declaration of fish nemo class
 *
 * represents a nemo fish in the aquarium
 *
 * provides functionality for drawing fish and handling click
 */
 
#include "pch.h"
#include "FishNemo.h"
#include "Aquarium.h"

using namespace std;

/// Fish filename
const wstring FishNemoImageName = L"images/nemo.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishNemo::FishNemo(Aquarium *aquarium) : Fish(aquarium, FishNemoImageName)
{
 SetRandomSpeed(20.0, 35.0, -10.0, 10.0);
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishNemo::XmlSave(wxXmlNode* node)
{
 auto itemNode = Fish::XmlSave(node);

 itemNode->AddAttribute(L"type", L"nemo");

 return itemNode;


}