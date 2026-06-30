// FUNC_NAME: Math::Matrix44::setMatrix
bool __thiscall Matrix44::setMatrix(const Matrix44& other) {
    // Snapshot original matrix values
    float old00 = data[0];
    float old01 = data[1];
    float old02 = data[2];
    float old03 = data[3];
    float old10 = data[4];
    float old11 = data[5];
    float old12 = data[6];
    float old13 = data[7];
    float old20 = data[8];
    float old21 = data[9];
    float old22 = data[10];
    float old23 = data[11];
    float old30 = data[12];
    float old31 = data[13];
    float old32 = data[14];
    float old33 = data[15];

    // Copy all elements from source matrix
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
    data[3] = other.data[3];
    data[4] = other.data[4];
    data[5] = other.data[5];
    data[6] = other.data[6];
    data[7] = other.data[7];
    data[8] = other.data[8];
    data[9] = other.data[9];
    data[10] = other.data[10];
    data[11] = other.data[11];
    data[12] = other.data[12];
    data[13] = other.data[13];
    data[14] = other.data[14];
    data[15] = other.data[15];

    // Return true if any element changed
    if (old12 != other.data[6] || old02 != other.data[2] ||
        old22 != other.data[10] || old32 != other.data[14] ||
        (old10 != other.data[4] || old00 != other.data[0] ||
         old20 != other.data[8] || old30 != other.data[12]) ||
        (old13 != other.data[7] || old03 != other.data[3] ||
         old23 != other.data[11] || old33 != other.data[15]) ||
        (old11 != other.data[5] || old01 != other.data[1] ||
         old21 != other.data[9] || old31 != other.data[13])) {
        return true;
    }
    return false;
}