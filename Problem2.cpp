#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
const int num_robots = 5; //Initializes numbers of robots
std::vector<bool> tools(num_robots,true); // Initializes vector to tract the availiability of the tools
std::vector<std::mutex> tool_mutexes(num_robots); // A mutex for each tool to ensure synced access
void performTask(int RobotID) { //Defines function that simulates each robot
    int leftTool = RobotID; //Adjust tool indices to match robot ID
    int rightTool = (RobotID + 1) % num_robots; // Ensures wrap around for the last robot
    std::unique_lock<std::mutex> lock1(tool_mutexes[leftTool], std::defer_lock); //Setup to lock tool later
    std::unique_lock<std::mutex> lock2(tool_mutexes[rightTool], std::defer_lock); //Setup to lock tool later
    std::lock(lock1,lock2); //Locks both tools at the same time
    if (tools[leftTool] && tools[rightTool]) { //Checks if tools can be picked up by robots
        tools[leftTool] = false; //Marks left tool as in use
        tools[rightTool] = false; //Marks right tool as in use
        std::cout << "Robot " << RobotID << " is collecting data." << std::endl; //Prints message to user
        std::this_thread::sleep_for(std::chrono::seconds(1)); //Simulates time for grabbing the tools
        std::cout << "Robot " << RobotID << " acquired tools and starts performing a task." << std::endl; //Prints message to user
        std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulates time to complete task and put tools back
        tools[leftTool] = true; //Marks left tool as not in use
        tools[rightTool] = true; //Marks right tool as not in use
        std::cout << "Robot " << RobotID << " finshed the task and returning the tools." << std::endl; //Prints message to user
    }
}
int main() {
    std::vector<std::thread> robotThreads; //Vector to hold threads that represent each robot
    auto start = std::chrono::high_resolution_clock::now(); //Start clock for calculating duration
    //Creates and starts each thread
    for (int i = 0; i < num_robots; ++i) {
        robotThreads.emplace_back(performTask, i);
    }
    //Waits for each thread to be complete
    for (auto &t : robotThreads) {
        t.join();
    }
    auto end = std::chrono::high_resolution_clock::now(); //Ends clock for calculating duration
    std::chrono::duration<double> duration = end - start; //Calculates duration
    std::cout << "Duration : " << duration.count() << " seconds" << std::endl; //Prints message to user
    return 0; //Returns 0 for successful execution
}