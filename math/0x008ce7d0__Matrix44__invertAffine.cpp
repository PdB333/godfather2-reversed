// FUNC_NAME: Matrix44::invertAffine
void __fastcall invertAffine(float *src, float *dst)
{
    // src is a 4x4 matrix (row-major) representing an affine transform:
    //   rows 0-2: rotation (top-left 3x3), row 3: translation (x,y,z,w)
    // Assumes rotation is orthonormal (so inverse = transpose).
    // dst receives the inverse transform:
    //   top-left 3x3 = transpose of src's rotation,
    //   last row = (-dot(translation, src_row0), -dot(translation, src_row1), -dot(translation, src_row2), 1.0f)

    // Load src rows (first 3 columns of each row)
    float r00 = src[0];  // +0x00
    float r01 = src[1];  // +0x04
    float r02 = src[2];  // +0x08
    // src[3] ignored (should be 0)

    float r10 = src[4];  // +0x10
    float r11 = src[5];  // +0x14
    float r12 = src[6];  // +0x18
    // src[7] ignored

    float r20 = src[8];  // +0x20
    float r21 = src[9];  // +0x24
    float r22 = src[10]; // +0x28
    // src[11] ignored

    float tx = src[12];  // +0x30
    float ty = src[13];  // +0x34
    float tz = src[14];  // +0x38
    float tw = src[15];  // +0x3C (homogeneous, expected to be 1.0f)

    // Write transposed rotation to dst (first three rows)
    dst[0]  = r00;  // +0x00
    dst[1]  = r10;  // +0x04
    dst[2]  = r20;  // +0x08
    dst[3]  = 0.0f; // +0x0C

    dst[4]  = r01;  // +0x10
    dst[5]  = r11;  // +0x14
    dst[6]  = r21;  // +0x18
    dst[7]  = 0.0f; // +0x1C

    dst[8]  = r02;  // +0x20
    dst[9]  = r12;  // +0x24
    dst[10] = r22;  // +0x28
    dst[11] = 0.0f; // +0x2C

    // Compute new translation: -R^T * t (where R is the rotation, t is translation)
    dst[12] = -(tx * r00 + ty * r01 + tz * r02); // +0x30
    dst[13] = -(tx * r10 + ty * r11 + tz * r12); // +0x34
    dst[14] = -(tx * r20 + ty * r21 + tz * r22); // +0x38
    dst[15] = 1.0f; // +0x3C (original code loads from global _DAT_00d5780c, which is likely 1.0f)
}