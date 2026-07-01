// FUNC_NAME: TransformMatrix::operatorAssign48Bytes

// Function at 0x00994890 copies 12 DWORDs (48 bytes) from source to destination.
// Appears to be a trivial member assignment for a transformation matrix (4x3 float or 3x4) or similar 12-element struct.
struct TransformMatrix {
    unsigned int data[12]; // 12 DWORDs, could be floats for a 4x3 matrix

    void __thiscall operatorAssign48Bytes(const TransformMatrix& other) {
        // Copy 12 DWORDs (48 bytes) from other to this
        this->data[0] = other.data[0];
        this->data[1] = other.data[1];
        this->data[2] = other.data[2];
        this->data[3] = other.data[3];
        this->data[4] = other.data[4];
        this->data[5] = other.data[5];
        this->data[6] = other.data[6];
        this->data[7] = other.data[7];
        this->data[8] = other.data[8];
        this->data[9] = other.data[9];
        this->data[10] = other.data[10];
        this->data[11] = other.data[11];
    }
};