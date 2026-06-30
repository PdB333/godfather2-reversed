// FUNC_NAME: vec3Magnitude
// Function address: 0x004bcfb0
// Role: Calculates the Euclidean length (magnitude) of a 3D float vector.
#include <cmath>

double vec3Magnitude(const float* vec) {
    return std::sqrt(
        static_cast<double>(vec[0]) * static_cast<double>(vec[0]) +
        static_cast<double>(vec[1]) * static_cast<double>(vec[1]) +
        static_cast<double>(vec[2]) * static_cast<double>(vec[2])
    );
}