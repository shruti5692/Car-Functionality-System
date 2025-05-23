#ifndef CAR_H
#define CAR_H

enum class GearType { PARK, REVERSE, NEUTRAL, DRIVE };

struct Location {
    double latitude;
    double longitude;
};

class Car {
private:
    GearType gearState;
    double speed;
    Location currentLocation;
    Location destination;

    double calculateDistance(const Location& loc1, const Location& loc2) const;

public:
    Car();

    void accelerate(double value);
    void brake(double value);
    void shiftGear(GearType newGear);

    GearType getGearState() const;
    double getSpeed() const;
    Location getLocation() const;
    Location getDestination() const;

    void setDestination(const Location& dest);
    void drive(double timeInHours);
    double timeToDestination() const;
    bool hasArrived() const;
};

#endif 
