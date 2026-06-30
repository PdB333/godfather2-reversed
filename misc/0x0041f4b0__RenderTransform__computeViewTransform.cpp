// FUNC_NAME: RenderTransform::computeViewTransform
void __thiscall RenderTransform::computeViewTransform(float* this, float* inputScale, void* fromTransform, void* toTransform, int time) {
    float fTime = (float)time;
    float fromScaleZ = this[10];    // +0x28 from this (float array)
    float fromScaleX = this[0];     // +0x00
    float toScaleX = inputScale[0];
    float toScaleZ = inputScale[10]; // +0x28 from inputScale

    // Compute scaling factors from this (render transform) and inputScale (view/camera?)
    this[1] = this[5] / inputScale[5]; // Y scale factor
    this[3] = 1.0f; // Hardcoded? Actually DAT_00e2b1a4 is likely 1.0f
    this[0] = fromScaleX / toScaleX;  // X scale factor
    this[2] = fromScaleZ / toScaleZ;  // Z scale factor

    // Get source and destination points from transforms (offsets 0x30 = 12 floats into struct)
    float srcX = *(float*)((char*)fromTransform + 0x30);
    float srcY = *(float*)((char*)fromTransform + 0x34);
    float srcZ = *(float*)((char*)fromTransform + 0x38);
    float srcW = *(float*)((char*)fromTransform + 0x3c);

    float dstX = *(float*)((char*)toTransform + 0x30);
    float dstY = *(float*)((char*)toTransform + 0x34);
    float dstZ = *(float*)((char*)toTransform + 0x38);
    float dstW = *(float*)((char*)toTransform + 0x3c);

    // Apply scaling to source to get intermediate point
    float outX = this[0] * srcX;
    float outY = this[1] * srcY;
    float outZ = this[2] * srcZ;
    float outW = this[3] * srcW;

    // Store intermediate
    this[4] = outX;
    this[5] = outY;
    this[6] = outZ;
    this[7] = outW;

    // Compute difference to destination (world space offset)
    float diffX = dstX - outX;
    float diffY = dstY - outY;
    float diffZ = dstZ - outZ;
    float diffW = dstW - outW;

    // Store difference (now in this[4..7])
    this[4] = diffX;
    this[5] = diffY;
    this[6] = diffZ;
    this[7] = diffW;

    // Apply a fixed 4x4 matrix transformation (global projection matrix)
    // Matrix elements at 0x011280b0..0x011280ec (16 floats)
    float m00 = *(float*)0x011280b0;
    float m01 = *(float*)0x011280b4;
    float m02 = *(float*)0x011280b8;
    float m03 = *(float*)0x011280bc;
    float m10 = *(float*)0x011280c0;
    float m11 = *(float*)0x011280c4;
    float m12 = *(float*)0x011280c8;
    float m13 = *(float*)0x011280cc;
    float m20 = *(float*)0x011280d0; // Not used? Actually missing in decompile, but likely present
    float m21 = *(float*)0x011280d4; // Not used
    float m22 = *(float*)0x011280d8; // Not used
    float m23 = *(float*)0x011280dc; // Not used
    float m30 = *(float*)0x011280e0;
    float m31 = *(float*)0x011280e4;
    float m32 = *(float*)0x011280e8;
    float m33 = *(float*)0x011280ec;

    // Compute transformed point using matrix multiplication (only rows 0 and 1 fully, but only partial? Actually decompile shows only some multiplies)
    float tx = diffX * m00 + this[0] * m30 + m10;
    float ty = diffY * m01 + this[1] * m31 + m11;
    float tz = diffZ * m02 + this[2] * m32 + m12;
    float tw = diffW * m03 + this[3] * m33 + m13;

    // Store transformed point
    this[4] = tx;
    this[5] = ty;
    this[6] = tz;
    this[7] = tw;

    // Time-based offset adjustment
    if (time < 0) {
        fTime = fTime + *(float*)0x00e44578;
    }
    this[5] = fTime * *(float*)0x00e44728 + this[5]; // Add vertical offset scaled by time

    return;
}