/**
 * @file ItemTest.cpp
 * @author Yeji Lee
 *
 * Unit tests for the Item class.
 *
 * Contains unit tests for the Item class using the Google Test framework.
 *
 * A mock, class, ItemMock, is used to test the functionality of the base Item class.
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Aquarium.h>

/// Fish filename
const std::wstring FishBetaImageName = L"images/beta.png";


/** Mock class for testing the class Item */
class ItemMock : public Item
{
public:
 ItemMock(Aquarium *aquarium) : Item(aquarium, FishBetaImageName) {}

 void Draw(wxDC *dc) override
 {

 }

};

/**
 * Verify the construction of an Item object.
 *
 * Checks that an ItemMock object can be created successfully with a reference to the aquarium.
 */
TEST(ItemTest, Construct) {
 Aquarium aquarium; // Creates an aquarium object
 ItemMock item(&aquarium); // Create an ItemMock object
}

/**
 * Test case for getters and setters in the Item class.
 *
 * Checks the functionality of the GetX, GetY, and SetLocation method in the Item class.
 */
TEST(ItemTest, GettersSetters){
 Aquarium aquarium;
 ItemMock item(&aquarium);

 // Test initial values
 ASSERT_NEAR(0, item.GetX(), 0.0001);
 ASSERT_NEAR(0, item.GetY(), 0.0001);

 // Test SetLocation, GetX, and GetY
 item.SetLocation(10.5, 17.2);
 ASSERT_NEAR(10.5, item.GetX(), 0.0001);
 ASSERT_NEAR(17.2, item.GetY(), 0.0001);

 // Test a second with with different values
 item.SetLocation(-72, -107);
 ASSERT_NEAR(-72, item.GetX(), 0.0001);
 ASSERT_NEAR(-107, item.GetY(), 0.0001);
}

/**
 * Test to ensure that HitTest works correctly for FishBeta.
 */
TEST(ItemTest, HitTest)
{
 // Create an Aquarium object to hold the fish
 Aquarium aquarium;

 // Create a FishBeta object inside the aquarium
ItemMock fish(&aquarium);

 // Set a location for the fish in the aquarium
 // Numbers are chosen to easily differentiate them
 fish.SetLocation(100, 200);

 // Test if the HitTest function correctly identifies a click on the center of the fish
 ASSERT_TRUE(fish.HitTest(100, 200));

 // Test if HitTest correctly identifies a miss to the left of the fish
 ASSERT_FALSE(fish.HitTest(10, 200));

 // Test if HitTest correctly identifies a miss to the right of the fish
 ASSERT_FALSE(fish.HitTest(200, 200));

 // Test if HitTest correctly identifies a miss above the fish
 ASSERT_FALSE(fish.HitTest(100, 0));

 // Test if HitTest correctly identifies a miss below the fish
 ASSERT_FALSE(fish.HitTest(100, 300));

 // Test a transparent pixel location on the fish (adjust values based on actual bitmap size)
 ASSERT_FALSE(fish.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));
}
