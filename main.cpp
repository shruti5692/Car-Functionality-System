#include "Car.h"
#include <iostream>

int main() {
    Car myCar;

    std::cout << "Select gear:\n";
    std::cout << "0 - PARK\n1 - REVERSE\n2 - NEUTRAL\n3 - DRIVE\n";
    int gearInput;
    std::cin >> gearInput;

    if (gearInput < 0 || gearInput > 3) {
        std::cout << "Invalid gear input!" << std::endl;
        return 1;
    }

    myCar.shiftGear(static_cast<GearType>(gearInput));

    std::cout << "Enter acceleration value: ";
    double acceleration;
    std::cin >> acceleration;
    myCar.accelerate(acceleration);

    std::cout << "Enter destination latitude and longitude: ";
    double lat, lon;
    std::cin >> lat >> lon;

    Location destination = {lat, lon};
    myCar.setDestination(destination);

    std::cout << "Enter time in hours to drive: ";
    double hours;
    std::cin >> hours;

    myCar.drive(hours);

    std::cout << "\n--- Status ---" << std::endl;
    std::cout << "Current Speed: " << myCar.getSpeed() << " km/h" << std::endl;
    std::cout << "Time to Destination: " << myCar.timeToDestination() << " hours" << std::endl;

    if (myCar.hasArrived()) {
        std::cout << "You have arrived at the destination!" << std::endl;
    } else {
        std::cout << "You are still on the way." << std::endl;
    }

    return 0;
}
