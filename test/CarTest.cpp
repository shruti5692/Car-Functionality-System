#include <iostream>
#include <cassert>
#include "../src/Car.h"

void testInitialState() {
    Car car;
    assert(car.getSpeed() == 0);
    assert(car.getGearState() == GearType::PARK);

    Location loc = car.getLocation();
    Location dest = car.getDestination();

    assert(loc.latitude == 0);
    assert(loc.longitude == 0);
    assert(dest.latitude == 0);
    assert(dest.longitude == 0);
}

void testSetAndGetDestination() {
    Car car;
    Location destination{10.0, 20.0};
    car.setDestination(destination);
    Location dest = car.getDestination();
    assert(dest.latitude == 10.0);
    assert(dest.longitude == 20.0);
}

void testAccelerateAndBrake() {
    Car car;
    car.shiftGear(GearType::DRIVE);  // Shift to DRIVE before accelerating

    car.accelerate(50);
    assert(car.getSpeed() == 50);

    car.brake(20);
    assert(car.getSpeed() == 30);

    // Brake more than speed, speed should not go negative
    car.brake(100);
    assert(car.getSpeed() == 0);

    // Accelerate by zero and negative value should not reduce speed
    car.accelerate(0);
    assert(car.getSpeed() == 0);
    car.accelerate(-10);
    assert(car.getSpeed() == 0);

    // Brake by zero and negative value should not change speed
    car.brake(0);
    assert(car.getSpeed() == 0);
    car.brake(-5);
    assert(car.getSpeed() == 0);
}

void testGearShift() {
    Car car;
    car.shiftGear(GearType::DRIVE);
    assert(car.getGearState() == GearType::DRIVE);

    car.shiftGear(GearType::REVERSE);
    assert(car.getGearState() == GearType::REVERSE);

    car.shiftGear(GearType::NEUTRAL);
    assert(car.getGearState() == GearType::NEUTRAL);

    car.shiftGear(GearType::PARK);
    assert(car.getGearState() == GearType::PARK);
}

void testDriveAndArrival() {
    Car car;
    car.setDestination(Location{5.0, 0.0});
    car.shiftGear(GearType::DRIVE);
    car.accelerate(10);  // speed = 10 units/hour

    car.drive(0); // drive zero time
    assert(car.getSpeed() == 10);
    assert(car.hasArrived() == false);

    car.drive(0.25);  // drive for 0.25 hour at speed 10 = move ~2.5 units latitude
    Location locAfter = car.getLocation();

    // Latitude should have increased and be no more than 2.5
    assert(locAfter.latitude > 0);
    assert(locAfter.latitude <= 2.5);

    car.drive(1.0);  // drive 1 more hour
    assert(car.hasArrived() == true);

    Location locFinal = car.getLocation();
    assert(locFinal.latitude == 5.0);
    assert(locFinal.longitude == 0.0);

    double timeLeft = car.timeToDestination();
    assert(timeLeft <= 0);
}

void testTimeToDestination() {
    Car car;
    car.setDestination(Location{10.0, 0.0});
    car.shiftGear(GearType::DRIVE);

    // Speed zero: timeToDestination() should return a large value but finite
    double timeZeroSpeed = car.timeToDestination();
    assert(timeZeroSpeed < 1e9);

    car.accelerate(20);
    double time = car.timeToDestination();

    assert(time > 0);
    assert(time < 1000);
}

void testSameLocationArrival() {
    Car car;
    car.setDestination(Location{0.0, 0.0});
    assert(car.hasArrived() == true);
}

int main() {
    std::cout << "Running Car class tests...\n";

    testInitialState();
    testSetAndGetDestination();
    testAccelerateAndBrake();
    testGearShift();
    testDriveAndArrival();
    testTimeToDestination();
    testSameLocationArrival();

    std::cout << "All tests passed successfully!\n";
    return 0;
}
