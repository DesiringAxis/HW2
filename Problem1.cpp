#include <iostream>
#include <string>
#include <memory>
#include <vector>
//1.1
class Sensor { //Defines new abstract base class "Sensor"
    public: //Ensures accessibility outside the class "Sensor"
        virtual ~Sensor() {} //Declares a virtual destructor for the Sensor class with the instructions {}
        virtual void gatherData() = 0; // Declares a virtual function for data gathering
        virtual void processData() = 0; // Declares a virtual function for data processing
};
//1.2
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
//1.3
class SensorFactory { //Defines new class "SensorFactory"
    public: //Ensure accessibility outside the class "SensoryFactory"
        static Sensor* createSensor(const std::string& type) { //Implements a static function that matches certain string inputs to an output
            if (type == "Fuel Flow") { //Checks if "FuleFlow" string was inputted
                return new FuelFlowSensor(); // Return a pointer to the "FuelFlowSensor" class
            }
            else if (type == "AOA") { //Checks if "AOA" string was inputted
                return new AOASensor(); // Return a pointer to the "AOASensor" class
            }
            else if (type == "Cabin Pressure") { //Checks if "CabinPressure" string was inputted
                return new CabinPressureSensor(); // Return a pointer to the "CabinPressureSensor" class
            }
            else { //If none of the above strings matches
                return nullptr; // Returns a null pointer
            }
        }
};
//1.4
class AerospaceControlSystem { //Defines new class "AerospaceControlSystem"
    private: //Ensure accessibility only inside the class "AerospaceControlSystem"
        std::vector<Sensor*> sensors; //Stores pointers to the sensors in the control system
    public: //Ensure accessibility outside the class "AerospaceControlSystem"
        void addSensor(Sensor* sensor) { //Adds a new sensor in the control system
            sensors.push_back(sensor); //Adds a given sensor to the back of the sensor list
        }
        void monitorAndAdjust() { //Defines new function for sensor data gathering and processing
            for (Sensor* sensor : sensors) { //Loop to go through all 3 sensors in the system
                sensor->gatherData(); //Collects data from the current sensor
                sensor->processData(); //Process the collected data from current sensor
                std::cout << "Adjusting controls based on sensor data" << std::endl; //Prints out text to the user
            }
        }
};
//1.5
int main() {
    AerospaceControlSystem ctrlSys; //Start an instance of the class "AerospaceControlSystem"
    Sensor* fuelFlowSensor = SensorFactory::createSensor("Fuel Flow"); //Create a fuel flow sensor using the class "SensorFactory"
    Sensor* aoaSensor = SensorFactory::createSensor("AOA"); //Create a angle of attack sensor using the class "SensorFactory"
    Sensor* cabinPressureSensor = SensorFactory::createSensor("Cabin Pressure"); //Create a cabin pressure sensor using the class "SensorFactory"
    //Checks if each created sensor are not null pointers and then adds them to the control system
    if(fuelFlowSensor != nullptr) {
        ctrlSys.addSensor(fuelFlowSensor);
    }
    if(aoaSensor != nullptr) {
        ctrlSys.addSensor(aoaSensor);
    }
    if(cabinPressureSensor != nullptr) {
        ctrlSys.addSensor(cabinPressureSensor);
    }
    ctrlSys.monitorAndAdjust(); //Monitors and adjusts the control system based on the sensor data
    // Cleans up dynmanically allocated memory
    delete fuelFlowSensor;
    delete aoaSensor;
    delete cabinPressureSensor;
    return 0; //Returns 0 for successful execution
};