/**
 * @file Fish.h
 * @author Yeji Lee
 *
 *
 */
 
#ifndef FISH_H
#define FISH_H

#include "Item.h"

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class Fish : public Item {
private:
 /**
  * speed of x coordinate
  */
 double mSpeedX = 0;;

 /**
  * speed of y coordinate
  */
 double mSpeedY= 0;;


protected:
 /**
  * constructor foer fish object
  * @param aquarium the aquarium to whic this fish belongs
  * @param filename the image file name representing the fish
  */
 Fish(Aquarium* aquarium, const std::wstring& filename);

 /**
  * background member
  */
 std::unique_ptr<wxBitmap> mBackground;

 /**
  *set random speed for fish within the specified range
  *
  * @param minX minimum speed of x coordinate
  * @param maxX maximum speed of x coordinate
  * @param minY minimum speed of y coordinate
  * @param maxY maximum speed of y coordinate
  */
 void SetRandomSpeed(double minX, double maxX, double minY, double maxY);



public:

 Fish() = delete;


 Fish(const Fish &) = delete;


 void operator=(const Fish &) = delete;

 /**
  * updates the fish poisition based on the elapsed time
  * called to update fish movement in aquairum
  * @param elapsed the time since the last update in seconds
  */
 void Update(double elapsed)override;

 /**
  * speed of the fish in both x and y coordinate
  * @param speedX speed in x coordinate in pixels
  * @param speedY speed in y coordinate in pixel
  */
 void SetSpeed(double speedX, double speedY){mSpeedX = speedX; mSpeedY = speedY;}

 /**
  *
  * @param node the [parent xml node to which this fish data will be saved
  * @return a pointer to the new XML node created for this fish
  */
 wxXmlNode* XmlSave(wxXmlNode* node) override;

 void XmlLoad(wxXmlNode* node);

 /**
  * get current speed of the fish in x coordinate
  * @return speed in x coordinate in pixels
  */
 double GetSpeedX(){return mSpeedX;}

 /**
  * get current speed of the fish in y coordinate
  * @return speed in y coordinate in pixels
  */
 double GetSpeedY(){return mSpeedY;}


};



#endif //FISH_H
