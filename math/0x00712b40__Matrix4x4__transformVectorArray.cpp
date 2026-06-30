// FUNC_NAME: Matrix4x4::transformVectorArray
// 0x00712b40: Transforms an array of 4D vectors by a 4x4 matrix (row-major storage, column-wise multiplication)
// 'this' points to a 16-float matrix ( row-major: m[0][0]..m[3][3] at offsets 0..15 )
// param_1: source array of 4*count floats (interleaved x,y,z,w)
// param_2: destination array (interleaved x,y,z,w)
// count: passed in EAX (unusual; treated as third parameter)
void __thiscall Matrix4x4::transformVectorArray(float* src, float* dst) {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
    int count;  // originally in EAX, not in parameter list

    // load matrix columns (row-major storage, but we use column vectors)
    // offset +0x00
    m00 = this[0];   // row0 col0
    m01 = this[1];   // row0 col1
    m02 = this[2];
    m03 = this[3];
    // offset +0x04
    m10 = this[4];   // row1 col0
    m11 = this[5];
    m12 = this[6];
    m13 = this[7];
    // offset +0x08
    m20 = this[8];
    m21 = this[9];
    m22 = this[10];
    m23 = this[11];
    // offset +0x0C
    m30 = this[12];
    m31 = this[13];
    m32 = this[14];
    m33 = this[15];

    // count is passed in EAX (original code)
    // assume it's a member variable or have been set before call
    // for reconstruction we treat it as an implicit parameter
    // In the original the count is in register EAX, we'll just loop while count>0
    // but since it's not declared, we'll use a local variable set by the caller.
    // For clarity, we'll assume the function is called with an implicit count.
    // The actual call site passes count in EAX, so we'll declare it as 'int count' but the signature doesn't show it.
    // To match the original calling convention, we keep it as is.
    // We'll just name it 'count' and note it's from EAX.
    int count; // this is passed in EAX, not reflected in signature
    // The decompiler shows 'int in_EAX' but no parameter; we'll use it as loop bound.

    if (count > 0) {
        do {
            float vx = src[0];
            float vy = src[1];
            float vz = src[2];
            float vw = src[3];

            // transform: dot vector with each column (M^T * v or v * M)
            dst[0] = vx * m00 + vy * m10 + vz * m20 + vw * m30;
            dst[1] = vx * m01 + vy * m11 + vz * m21 + vw * m31;
            dst[2] = vx * m02 + vy * m12 + vz * m22 + vw * m32;
            dst[3] = vx * m03 + vy * m13 + vz * m23 + vw * m33;

            src += 4;
            dst += 4;
            count--;
        } while (count > 0);
    }
}