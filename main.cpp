#include "Car.h"
#include <iostream>

int main() {
    Car myCar;
    myCar.shiftGear(GearType::DRIVE);
    myCar.accelerate(80);

    Location pune = {18.5204, 73.8567};
    Location mumbai = {19.0760, 72.8777};

    myCar.setDestination(mumbai);
    std::cout << "Driving from Pune to Mumbai..." << std::endl;

    myCar.drive(1.5); // drive for 1.5 hours

    std::cout << "Current Speed: " << myCar.getSpeed() << " km/h\n";
    std::cout << "Time to destination: " << myCar.timeToDestination() << " hours\n";

    if (myCar.hasArrived()) {
        std::cout << "Arrived at destination.\n";
    } else {
        std::cout << "Still on the way.\n";
    }

    return 0;
}
