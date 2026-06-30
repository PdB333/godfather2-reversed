// FUNC_NAME: Quaternion::scaleAndAdd
// Function address: 0x005c7060
// Role: Performs a linear combination of two quaternions (4-component vectors): result = t * this + other.
// Used for blending or interpolating quaternions (e.g., for animation blending or smooth transitions).

class Quaternion {
public:
    // Computes result = t * this + other and stores into result.
    // Params:
    //   other: pointer to 4 floats (the quaternion to add)
    //   t: scalar multiplier for this quaternion
    //   result: pointer to output 4-float array
    void __thiscall scaleAndAdd(const float* other, float t, float* result) const;
};

void __thiscall Quaternion::scaleAndAdd(const float* other, float t, float* result) const {
    // Read components of this (the implicit 'this' pointer)
    float this_x = this[0];
    float this_y = this[1];
    float this_z = this[2];
    float this_w = this[3];

    // Read components of the other quaternion
    float other_x = other[0];
    float other_y = other[1];
    float other_z = other[2];
    float other_w = other[3];

    // Compute linear combination: result = t * this + other
    result[0] = t * this_x + other_x;
    result[1] = t * this_y + other_y;
    result[2] = t * this_z + other_z;
    result[3] = t * this_w + other_w;
}