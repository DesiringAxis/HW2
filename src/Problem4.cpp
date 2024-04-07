#include "matplotlibcpp.h"
#include <vector>
#include <cmath>

namespace plt = matplotlibcpp;

int main() {
    // Aerodynamic constants
    double rho = 1.225; // Air density (kg/m^3)
    double S = 30.0; // Wing area (m^2)
    double CL = 0.5; // Lift coefficient
    double half_rho_S_CL = 0.5 * rho * S * CL; // Precompute lift equation

    // Velocity range from 0 to 100 m/s with 100 points
    std::vector<double> velocity(100), lift(100);
    for (size_t i = 0; i < velocity.size(); ++i) {
        velocity[i] = i; // Velocity in m/s
        lift[i] = half_rho_S_CL * velocity[i] * velocity[i]; // Calculate lift
    }

    // Plotting
    plt::plot(velocity, lift);
    plt::xlabel("Velocity (m/s)");
    plt::ylabel("Lift (N)");
    plt::title("Lift vs Velocity");
    plt::show();

    return 0;
}