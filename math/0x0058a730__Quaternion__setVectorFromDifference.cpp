// FUNC_NAME: Quaternion::setVectorFromDifference
// Address: 0x0058a730
// Role: Subtracts the vector (x,y,z) parts of two quaternions, preserving the w component of the output.
// Used for computing quaternion delta/derivative when w is known from context.

struct Quaternion {
    float x, y, z, w;

    // Sets this->x,y,z = a - b, preserves this->w unchanged.
    void setVectorFromDifference(const Quaternion &a, const Quaternion &b) {
        float savedW = w;                // preserve original w
        x = a.x - b.x;
        y = a.y - b.y;
        z = a.z - b.z;
        w = savedW;                      // restore w (not modified)
    }
};