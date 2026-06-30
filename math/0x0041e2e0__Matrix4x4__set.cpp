// FUNC_NAME: Matrix4x4::set
bool __thiscall Matrix4x4::set(float* src) {
    // Store old values from this matrix (16 floats = 4x4)
    float old00 = this->m[0];
    float old01 = this->m[1];
    float old02 = this->m[2];
    float old03 = this->m[3];
    float old10 = this->m[4];
    float old11 = this->m[5];
    float old12 = this->m[6];
    float old13 = this->m[7];
    float old20 = this->m[8];
    float old21 = this->m[9];
    float old22 = this->m[10];
    float old23 = this->m[11];
    float old30 = this->m[12];
    float old31 = this->m[13];
    float old32 = this->m[14];
    float old33 = this->m[15];

    // Copy new values from source
    this->m[0] = src[0];
    this->m[1] = src[1];
    this->m[2] = src[2];
    this->m[3] = src[3];
    this->m[4] = src[4];
    this->m[5] = src[5];
    this->m[6] = src[6];
    this->m[7] = src[7];
    this->m[8] = src[8];
    this->m[9] = src[9];
    this->m[10] = src[10];
    this->m[11] = src[11];
    this->m[12] = src[12];
    this->m[13] = src[13];
    this->m[14] = src[14];
    this->m[15] = src[15];

    // Return true if any element changed
    if (old12 != src[6] || old02 != src[2] || old20 != src[10] || old30 != src[14] ||
        old10 != src[4] || old00 != src[0] || old20 != src[8] || old30 != src[12] ||
        old13 != src[7] || old03 != src[3] || old23 != src[11] || old33 != src[15] ||
        old11 != src[5] || old01 != src[1] || old21 != src[9] || old31 != src[13]) {
        return true;
    }
    return false;
}