// FUNC_NAME: EARSMatrix4x2::scale
// Function at 0x005145e0: Scales all 8 components of a 4x2 matrix by a scalar factor.
// The matrix is stored as 8 contiguous floats, likely row-major (4 rows, 2 columns).
class EARSMatrix4x2 {
public:
    /** Scales every element of the matrix by the given scalar. */
    void scale(float s) {
        // Row 0
        data[0] *= s;
        data[1] *= s;
        // Row 1
        data[2] *= s;
        data[3] *= s;
        // Row 2
        data[4] *= s;
        data[5] *= s;
        // Row 3
        data[6] *= s;
        data[7] *= s;
    }

private:
    float data[8]; // 4x2 matrix, data[row * 2 + col]
};