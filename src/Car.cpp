#include "Car.h"
#include <iostream>
#include <cmath>

Car::Car() : gearState(GearType::PARK), speed(0.0), currentLocation({0.0, 0.0}), destination({0.0, 0.0}) {}

void Car::accelerate(double value) {
    if (value <= 0) {
        return;  // ignore non-positive values
    }

    if (gearState == GearType::DRIVE || gearState == GearType::REVERSE) {
        speed += value;
    } else {
        std::cout << "Can't accelerate in current gear!" << std::endl;
    }
}


void Car::brake(double value) {
    if (value <= 0) return;  // ignore zero or negative values

    speed -= value;
    if (speed < 0) speed = 0;
}

void Car::shiftGear(GearType newGear) {
    gearState = newGear;
}

GearType Car::getGearState() const {
    return gearState;
}

double Car::getSpeed() const {
    return speed;
}

Location Car::getLocation() const {
    return currentLocation;
}

Location Car::getDestination() const {
    return destination;
}

void Car::setDestination(const Location& dest) {
    destination = dest;
}

double Car::calculateDistance(const Location& loc1, const Location& loc2) const {
    double dlat = loc2.latitude - loc1.latitude;
    double dlon = loc2.longitude - loc1.longitude;
    return std::sqrt(dlat * dlat + dlon * dlon);
}


void Car::drive(double timeInHours) {
    if (speed == 0) {
        std::cout << "Car is not moving!" << std::endl;
        return;
    }

    double distanceTravelled = speed * timeInHours;
    double totalDistance = calculateDistance(currentLocation, destination);

    if (distanceTravelled >= totalDistance) {
        currentLocation = destination;
    } else {
        double ratio = distanceTravelled / totalDistance;
        currentLocation.latitude += (destination.latitude - currentLocation.latitude) * ratio;
        currentLocation.longitude += (destination.longitude - currentLocation.longitude) * ratio;
    }

    //Always check after moving
    if (calculateDistance(currentLocation, destination) < 0.05) {
        currentLocation = destination;
    }
}


double Car::timeToDestination() const {
    double distanceLeft = calculateDistance(currentLocation, destination);
    return (speed == 0) ? -1 : distanceLeft / speed;
}

bool Car::hasArrived() const {
    return calculateDistance(currentLocation, destination) < 0.05; // approx. 50 meters
}
