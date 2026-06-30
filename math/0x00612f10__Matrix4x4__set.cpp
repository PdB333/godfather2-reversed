// FUNC_NAME: Matrix4x4::set
class Matrix4x4 {
public:
    // +0x00: 16 floats for 4x4 matrix
    float data[16];

    // Copies 16 floats from source to this->data and returns 1 if any element changed, else 0
    // Original calling convention: __fastcall (ECX = this, EDX = source)
    int __thiscall set(const float* source) {
        float old0 = data[0], old1 = data[1], old2 = data[2], old3 = data[3];
        float old4 = data[4], old5 = data[5], old6 = data[6], old7 = data[7];
        float old8 = data[8], old9 = data[9], old10 = data[10], old11 = data[11];
        float old12 = data[12], old13 = data[13], old14 = data[14], old15 = data[15];

        // Write source to this->data
        data[0] = source[0]; data[1] = source[1]; data[2] = source[2]; data[3] = source[3];
        data[4] = source[4]; data[5] = source[5]; data[6] = source[6]; data[7] = source[7];
        data[8] = source[8]; data[9] = source[9]; data[10] = source[10]; data[11] = source[11];
        data[12] = source[12]; data[13] = source[13]; data[14] = source[14]; data[15] = source[15];

        // Compare each saved old value with the corresponding source value
        if (old0 != source[0] || old1 != source[1] || old2 != source[2] || old3 != source[3] ||
            old4 != source[4] || old5 != source[5] || old6 != source[6] || old7 != source[7] ||
            old8 != source[8] || old9 != source[9] || old10 != source[10] || old11 != source[11] ||
            old12 != source[12] || old13 != source[13] || old14 != source[14] || old15 != source[15]) {
            return 1;
        }
        return 0;
    }
};