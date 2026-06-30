// FUNC_NAME: Matrix3x4::setScaled
// Function address: 0x0056b300
// Role: Scales a 3x4 matrix (stored column-major, 4 rows, 3 columns) by a scaling vector.
// Source matrix is copied and scaled element-wise into this matrix.
// The fourth column (translation) is not modified.

class Matrix3x4 {
public:
    // Column-major storage: data[col * 4 + row]
    float data[12]; // 3 columns, 4 rows each

    // Sets this matrix to a scaled copy of source: this[i] = source[i] * scaleVec[col]
    void __thiscall setScaled(const float *source, const float *scaleVec);
};

void __thiscall Matrix3x4::setScaled(const float *source, const float *scaleVec) {
    float sx = scaleVec[0];
    float sy = scaleVec[1];
    float sz = scaleVec[2];

    // First column (indices 0-3)
    data[0] = source[0] * sx;
    data[1] = source[1] * sx;
    data[2] = source[2] * sx;
    data[3] = source[3] * sx;

    // Second column (indices 4-7)
    data[4] = source[4] * sy;
    data[5] = source[5] * sy;
    data[6] = source[6] * sy;
    data[7] = source[7] * sy;

    // Third column (indices 8-11)
    data[8] = source[8] * sz;
    data[9] = source[9] * sz;
    data[10] = source[10] * sz;
    data[11] = source[11] * sz;

    // Note: Fourth column (indices 12-15) is unchanged.
}