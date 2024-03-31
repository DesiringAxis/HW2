#include <iostream>
#include <string>
class Sensor { //Defines new abstract class "Sensor"
    public: //Ensures accessibility outside the class "Sensor"
    virtual ~Sensor() {} //Declares a virtual destructor for the Sensor class with the instructions {}
    virtual void gatherData() = 0; // Declares a virtual function for data gathering
    virtual void processData() = 0; // Declares a virtual function for data processing
};