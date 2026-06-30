// Address: 0x004cd7e0 - Component-wise multiplication of two 4-element float vectors (likely Vector4 or RGBA color)
// This function multiplies each element of the 'this' vector by the corresponding element of 'other'
// and stores the result in 'result'. Equivalent to Hadamard product.

class Vector4 {
public:
    // Multiplies this vector component-wise with other and writes to result
    void componentwiseMultiply(const Vector4& other, Vector4& result) const {
        float a0 = data[0];
        float a1 = data[1];
        float a2 = data[2];
        float a3 = data[3];

        float b0 = other.data[0];
        float b1 = other.data[1];
        float b2 = other.data[2];
        float b3 = other.data[3];

        result.data[0] = a0 * b0;
        result.data[1] = a1 * b1;
        result.data[2] = a2 * b2;
        result.data[3] = a3 * b3;
    }

private:
    float data[4]; // +0x00 through +0x0C
};