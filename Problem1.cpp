#include <iostream>
#include <string>
#include <memory>
class Sensor { //Defines new abstract base class "Sensor"
    public: //Ensures accessibility outside the class "Sensor"
        virtual ~Sensor() {} //Declares a virtual destructor for the Sensor class with the instructions {}
        virtual void gatherData() = 0; // Declares a virtual function for data gathering
        virtual void processData() = 0; // Declares a virtual function for data processing
};
class FuelFlowSensor : public Sensor { //Defines new class "FuelFlowSensor" from the base class "Sensor"
    public: //Ensures accessibility outside the class "FuelFlowSensor"
        void gatherData() override { //Implent data gathering for the fuel flow sensor
            std::cout << "Gathering data from the fuel flow sensor" << std::endl; //Prints out text to the user
        }
        void processData() override { //Implent data processing for the fuel flow sensor
            std::cout << "Processing data from the fuel flow sensor" << std::endl; //Prints out text to the user
        }
};
class AOASensor : public Sensor { //Defines new class "AOASensor" from the base class "Sensor"
    public: //Ensures accessibility outside the class "AOASensor"
        void gatherData() override { //Implent data gathering for the angle of attack sensor
            std::cout << "Gathering data from the angle of attack sensor" << std::endl; //Prints out text to the user
        }
        void processData() override { //Implent data processing for the angle of attack sensor
            std::cout << "Processing data from the angle of attack sensor" << std::endl; //Prints out text to the user
        }
};
class CabinPressureSensor : public Sensor { //Defines new class "CabinPressureSensor" from the base class "Sensor"
    public: //Ensures accessibility outside the class "CabinPressureSensor"
        void gatherData() override { //Implent data gathering for the cabin pressure sensor
            std::cout << "Gathering data from the cabin pressure sensor" << std::endl; //Prints out text to the user
        }
        void processData() override { //Implent data processing for the cabin pressure sensor
            std::cout << "Processing data from the cabin pressure sensor" << std::endl; //Prints out text to the user
        }
};
class SensorFactory { //Defines new class "SensorFactory"
    public: //Ensure accessibility outside the class "SensoryFactory"
        static Sensor* createSensor(const std::string& type) { //Implements a static function that matches certain string inputs to an output
            if (type == "Fuel Flow") { //Checks if "Fule Flow" string was inputted
                return new FuelFlowSensor(); // Return a pointer to the "FuelFlowSensor" class
            }
            else if (type == "AOA") { //Checks if "AOA" string was inputted
                return new AOASensor(); // Return a pointer to the "AOASensor" class
            }
            else if (type == "Cabin Pressure") { //Checks if "Cabin Pressure" string was inputted
                return new CabinPressureSensor(); // Return a pointer to the "CabinPressureSensor" class
            }
            else { //If none of the above strings matches
                return nullptr; // Returns a null pointer
            }
        }
};