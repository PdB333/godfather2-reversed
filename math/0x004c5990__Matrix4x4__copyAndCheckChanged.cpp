// FUNC_NAME: Matrix4x4::copyAndCheckChanged
bool Matrix4x4::copyAndCheckChanged(const float* source) {
    float oldData[16];

    // Save all 16 floats from this matrix before overwriting
    for (int i = 0; i < 16; i++) {
        oldData[i] = m_data[i];
    }

    // Copy 16 floats from source to this matrix
    for (int i = 0; i < 16; i++) {
        m_data[i] = source[i];
    }

    // Check if any element changed; return true if at least one differed
    return (oldData[0] != source[0]) || (oldData[1] != source[1]) ||
           (oldData[2] != source[2]) || (oldData[3] != source[3]) ||
           (oldData[4] != source[4]) || (oldData[5] != source[5]) ||
           (oldData[6] != source[6]) || (oldData[7] != source[7]) ||
           (oldData[8] != source[8]) || (oldData[9] != source[9]) ||
           (oldData[10] != source[10]) || (oldData[11] != source[11]) ||
           (oldData[12] != source[12]) || (oldData[13] != source[13]) ||
           (oldData[14] != source[14]) || (oldData[15] != source[15]);
}