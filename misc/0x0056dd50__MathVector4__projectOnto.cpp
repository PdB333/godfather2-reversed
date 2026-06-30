// FUNC_NAME: MathVector4::projectOnto
// Function address: 0x0056dd50
// Purpose: Project a 3D vector onto a direction vector (ignoring w), storing the result in this 4D vector, preserving this->w.
// Parameters:
//   direction: 4D vector (only x,y,z used for direction; w ignored in projection but multiplied then overwritten)
//   source: 3D vector (x,y,z) to project
// Returns: 1 if direction length > epsilon, 0 otherwise (and sets result to zero)

#include <cmath>  // for fabs

class MathVector4 {
public:
    float x, y, z, w;

    // Project source onto direction and store in this->x,y,z (w unchanged)
    int projectOnto(const float direction[4], const float source[3]) {
        float sx = direction[0];
        float sy = direction[1];
        float sz = direction[2];
        float sqLength = sx * sx + sy * sy + sz * sz;

        // Squared length must be above a small epsilon to avoid division by zero
        // Original code uses a bitmask trick for absolute value; simplified here.
        const float kEpsilonSq = 0.000001f; // approximate
        if (fabs(sqLength) > kEpsilonSq) {
            // Save original w of this
            float savedW = this->w;  // in_EAX[3]
            // Projection scalar: dot(source, direction) / dot(direction, direction)
            float scalar = (source[0] * sx + source[1] * sy + source[2] * sz) / sqLength;
            // Compute result components (note: uses all 4 components of direction, but w is overwritten)
            this->x = scalar * direction[0];
            this->y = scalar * direction[1];
            this->z = scalar * direction[2];
            this->w = scalar * direction[3];  // temporary assignment
            this->w = savedW;                 // restore original w
            return 1;
        } else {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
            return 0;
        }
    }
};