#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
std::mutex mtx; //Mutex for protecting shared state
std::condition_variable cv_runway; //Condition varialbe for waking up ATC
bool ATCasleep = true; //ATC starts off asleep
int TrafficPattern = 0; //No traffic in the pattern intially
bool RunwayOccupied = false; //No traffic on the runway intially
const int MaxTrafficPattern = 3; //Maximum number of aircraft in the pattern
void aircraft(int id) { //Function for the simulation
    {
        std::unique_lock<std::mutex> lock(mtx); //Acquires a lock on mtx
        if (TrafficPattern >= MaxTrafficPattern) { //Sends aircraft to another airport if the pattern is full
            std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport." << std::endl; //Prints message to user
            std::cout << "Aircraft #" << id << " flying to another airport." << std::endl; //Prints message to user
            return; //Aircraft diverted
        }
        TrafficPattern++; //Adds to the TrafficPattern counter when aircraft requests to land
        std::cout << "Aircraft #" << id << " requesting landing." << std::endl; //Prints message to user
        if (ATCasleep) { //Checks if ATC is asleep
            ATCasleep = false; // Wakes up ATC
        }
        cv_runway.wait(lock, []{ return !RunwayOccupied; }); //Wait until runways is not occupied
        RunwayOccupied = true;// Set the runway to be occupied
        std::cout << "Aircraft #" << id << " is cleared to land." << std::endl; //Prints message to user
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000)); //Simulates 1 second for landing
    {
        std::lock_guard<std::mutex> lock(mtx); //Auto locks the mtx and releases it at the end of the scope
        RunwayOccupied = false; //Set the runway to be not occupied
        TrafficPattern--; //Removes aircraft from traffic pattern counter
        std::cout << "Runway is now free." << std::endl; //Prints message to user
        cv_runway.notify_one();//Notify one waiting aircraft that the runway is available
        if (TrafficPattern == 0) { //Checks if any aircraft are in the pattern
            ATCasleep = true; //Set ATC to asleep
        }
    }
}
int main() {
    std::vector<std::thread> aircrafts; //Vector to hold threads that represent each aircraft
    auto start = std::chrono::high_resolution_clock::now(); //Start clock for calculating duration
    //Creates and starts each thread
    for (int i = 1; i <= 10; i++) {
        aircrafts.emplace_back(aircraft, i);
    }
    //Waits for each thread to be complete
    for (auto& a : aircrafts) {
        a.join();
    }
    auto end = std::chrono::high_resolution_clock::now(); //Ends clock for calculating duration
    std::chrono::duration<double> duration = end - start; //Calculates duration
    std::cout << "Duration : " << duration.count() << " seconds" << std::endl; //Prints message to user
    return 0;
}