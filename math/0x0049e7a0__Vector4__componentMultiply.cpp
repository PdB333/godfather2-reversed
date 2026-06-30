// FUNC_NAME: Vector4::componentMultiply
class Vector4 {
public:
    // Member function: element-wise multiplication of this vector with another vector, storing result in output
    // Equivalent to Hadamard product for 4D vectors
    void componentMultiply(const float* other, float* output) const {
        // Multiply each component of this vector with the corresponding component of the other vector
        output[0] = this->x * other[0];
        output[1] = this->y * other[1];
        output[2] = this->z * other[2];
        output[3] = this->w * other[3];
    }

    // Assume members are ordered as x, y, z, w
    float x, y, z, w;
};