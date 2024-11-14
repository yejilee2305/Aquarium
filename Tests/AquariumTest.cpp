#include <pch.h>
#include <gtest/gtest.h>
#include <Aquarium.h>
#include <FishBeta.h>
#include <Item.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>
#include <FishNemo.h>
#include <FishDory.h>
#include <DecorCastle.h>
#include <Fish.h>

using namespace std;

const unsigned int RandomSeed = 1238197374;


class AquariumTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/aquarium";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }

    /**
 * Test to ensure an aquarium .aqua file is empty
 */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));

    }

    /**
 *  Populate an aquarium with three Beta fish
 */
    void PopulateThreeBetas(Aquarium *aquarium)
    {
        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);

        auto fish3 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);
    }

    void TestThreeBetas(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
    }

    void PopulateAllTypes(Aquarium *aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);

        auto castle = make_shared<DecorCastle>(aquarium);
        aquarium->Add(castle);
        castle->SetLocation(100, 200);

        auto beta = make_shared<FishBeta>(aquarium);
        aquarium->Add(beta);
        beta->SetLocation(400, 400);

        auto nemo = make_shared<FishNemo>(aquarium);
        aquarium->Add(nemo);
        nemo->SetLocation(600, 100);

        auto dory = make_shared<FishDory>(aquarium);
        aquarium->Add(dory);
        dory->SetLocation(600, 100);
    }

    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"castle\"/><item.* type=\"beta\"/><item.* type=\"nemo\"/><item.* type=\"dory\"/></aqua>")));
    }
};

TEST_F(AquariumTest, Construct){
    Aquarium aquarium;
}

/**
 * Test the HitTest function in the Aquarium class.
 */
TEST_F(AquariumTest, HitTest)
{
    // Create an aquarium
    Aquarium aquarium;

    // Test hitting an empty aquarium
    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) << L"Testing empty aquarium";

    // Create a FishBeta and add it to the aquarium
    auto fish1 = std::make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    // Test hitting the fish at its location
    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) << L"Testing fish at 100, 200";

    // Test hitting a location where there is no fish
    ASSERT_EQ(aquarium.HitTest(500, 500), nullptr) << L"Testing hit where there is no fish";
}

TEST_F(AquariumTest, HitTestOverlap)
{
    // Create an aquarium
    Aquarium aquarium;

    // Create two FishBeta objects and add them to the aquarium
    auto fish1 = std::make_shared<FishBeta>(&aquarium);
    auto fish2 = std::make_shared<FishBeta>(&aquarium);

    // Add fish to the aquarium (order matters!)
    aquarium.Add(fish1);  // fish1 is added first (on the bottom)
    aquarium.Add(fish2);  // fish2 is added second (on top)

    // Set both fish to the same location (overlapping)
    fish1->SetLocation(100, 200);
    fish2->SetLocation(100, 200);


    // Test hitting the location where both fish are located
    auto hitItem = aquarium.HitTest(100, 200);

    if (hitItem == fish2) {
        std::cout << "Correctly hit fish2 (on top)\n";
    } else if (hitItem == fish1) {
        std::cout << "Incorrectly hit fish1 (on bottom)\n";
    } else {
        std::cout << "Hit nothing (nullptr)\n";
    }

    ASSERT_TRUE(hitItem == fish2) << L"Testing fish2 is on top";

    // Test hitting a location where there is no fish
    ASSERT_EQ(aquarium.HitTest(500, 500), nullptr) << L"Testing hit where there is no fish";
}

TEST_F(AquariumTest, Save) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);
}

TEST_F(AquariumTest, Clear)
{
    Aquarium aquarium;
    PopulateThreeBetas(&aquarium);

    auto path = TempPath();
    auto fileBefore = path + L"/beforeClear.aqua";
    aquarium.Save(fileBefore);

    auto xmlBefore = ReadFile(fileBefore);
    cout << "Before Clear:\n" << xmlBefore << endl;
    ASSERT_FALSE(regex_search(xmlBefore, wregex(L"<aqua/>")));

    aquarium.Clear(fileBefore);

    auto fileAfter = path + L"/after.aqua";
    aquarium.Save(fileAfter);

    auto xmlAfter = ReadFile(fileAfter);
    cout << "After Clear:\n" << xmlAfter << endl;
    ASSERT_TRUE(regex_search(xmlAfter, wregex(L"<aqua/>")));
}

TEST_F(AquariumTest, Load) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;
    Aquarium aquarium2;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    aquarium2.Load(file1);
    aquarium2.Save(file1);
    TestEmpty(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);

    aquarium2.Load(file3);
    aquarium2.Save(file3);
    TestAllTypes(file3);
}

TEST_F(AquariumTest, FishBetaSpeedRange) {
    Aquarium aquarium;

    auto beta = make_shared<FishBeta>(&aquarium);
    aquarium.Add(beta);

    ASSERT_TRUE(beta->GetSpeedX() >= 10.0 && beta->GetSpeedX() <= 20.0);
    ASSERT_TRUE(beta->GetSpeedY() >= -5.0 && beta->GetSpeedY() <= 5.0);
}

TEST_F(AquariumTest, FishNemoSpeedRange) {
    Aquarium aquarium;

    auto nemo = make_shared<FishNemo>(&aquarium);
    aquarium.Add(nemo);

    ASSERT_TRUE(nemo->GetSpeedX() >= 20.0 && nemo->GetSpeedX() <= 35.0);
    ASSERT_TRUE(nemo->GetSpeedY() >= -10.0 && nemo->GetSpeedY() <= 10.0);
}

TEST_F(AquariumTest, FishDorySpeedRange) {
    Aquarium aquarium;

    auto dory = make_shared<FishDory>(&aquarium);
    aquarium.Add(dory);

    ASSERT_TRUE(dory->GetSpeedX() >= 5.0 && dory->GetSpeedX() <= 15.0);
    ASSERT_TRUE(dory->GetSpeedY() >= -2.5 && dory->GetSpeedY() <= 2.5);
}