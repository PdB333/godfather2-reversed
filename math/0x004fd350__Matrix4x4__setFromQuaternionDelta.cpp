// FUNC_NAME: Matrix4x4::setFromQuaternionDelta
void __thiscall Matrix4x4::setFromQuaternionDelta(float *this, float *quatA, float *quatB)
{
    // Constants from global data
    const float ONE = DAT_00e2b1a4;          // Typically 1.0f
    const float EPSILON = DAT_00e2cbe0;      // Small epsilon for zero check
    const float THRESHOLD = DAT_00e2cd58;    // Threshold for near-parallel detection (e.g., 0.9999f)
    const uint ABS_MASK = DAT_00e44680;      // 0x7FFFFFFF to get absolute value as float bits

    // Store quatA as the fourth row of the matrix (indices 12-15)
    this[12] = quatA[0];
    this[13] = quatA[1];
    this[14] = quatA[2];
    this[15] = quatA[3];

    // Compute the difference quaternion: quatB - quatA (store as third row, indices 8-11)
    float dx = quatB[0] - quatA[0];
    float dy = quatB[1] - quatA[1];
    float dz = quatB[2] - quatA[2];
    float dw = quatB[3] - quatA[3];
    this[8] = dx;
    this[9] = dy;
    this[10] = dz;
    this[11] = dw;

    // Normalize the difference vector to length ONE
    float lenSq = dx*dx + dy*dy + dz*dz + dw*dw;
    float invLen;
    if (lenSq <= EPSILON) {
        invLen = 0.0f;
    } else {
        invLen = ONE / sqrtf(lenSq);
    }
    float nx = dx * invLen;
    float ny = dy * invLen;
    float nz = dz * invLen;
    float nw = dw * invLen;

    // Determine which components are near-zero to avoid gimbal lock
    float a, b, c; // temporary cross product factors
    float absY = *((float*)&((uint&)ny & ABS_MASK)); // absolute value of ny as float
    float absX = *((float*)&((uint&)nx & ABS_MASK)); // absolute value of nx as float

    if (absY >= THRESHOLD) {
        // ny is near 1, use alternative basis
        a = 0.0f;
        if (absX < THRESHOLD) {
            c = ONE;
            b = 0.0f;
            goto computeCross;
        }
    } else {
        a = ONE;
        b = 0.0f;
    }
    c = 0.0f;

computeCross:
    // Compute first cross product: (a,b,c) × (nx, ny, nz)  (but note order: a*ny - b*nx? Actually the code does: 
    // *in_EAX = fStack_2c * fVar1 - fStack_28 * fVar9; where fVar1=ny, fVar9=nx? Wait careful: 
    // fVar1 = ny (since fVar1 = in_EAX[10]*invLen, and in_EAX[10] is dz? No, indices: 8=x,9=y,10=z,11=w. So fVar8 = dx*invLen = nx, fVar1 = dz*invLen = nz? Actually fVar1 = in_EAX[10]*invLen = dz*invLen = nz. fVar9 = in_EAX[9]*invLen = dy*invLen = ny. fVar2 = in_EAX[11]*invLen = dw*invLen = nw. So the normalized components are: nx (fVar8), ny (fVar9), nz (fVar1), nw (fVar2). So the cross product uses (a,b,c) with (nz, ny, nx)? Let's re-derive from code:
    // *in_EAX = fStack_2c * fVar1 - fStack_28 * fVar9;  // fVar1 = nz, fVar9 = ny
    // in_EAX[1] = fStack_28 * fVar8 - local_30 * fVar1; // fVar8 = nx
    // in_EAX[2] = local_30 * fVar9 - fStack_2c * fVar8; // fVar9 = ny, fVar8 = nx
    // So it's computing cross product of (fStack_2c, fStack_28, local_30) with (nz, ny, nx)? Actually the cross product of (a,b,c) and (nx,ny,nz) would be (b*nz - c*ny, c*nx - a*nz, a*ny - b*nx). But here we have (a*nz - b*ny, b*nx - c*nz, c*ny - a*nx). That's the negative of the cross product? Actually (a*nz - b*ny) = (b*ny - a*nz) * (-1). So it's the negative of the cross product? But then the next cross product uses the result. This might be intentional for right-handed coordinate system.
    // Given the complexity, I'll keep the exact computation as in the decompiled code.
    float cross1_x = a * nz - b * ny;
    float cross1_y = b * nx - c * nz;
    float cross1_z = c * ny - a * nx;
    float cross1_w = nw * 0.0f - nw * 0.0f; // always 0

    // Normalize the first cross product
    float lenSq2 = cross1_x*cross1_x + cross1_y*cross1_y + cross1_z*cross1_z + cross1_w*cross1_w;
    float invLen2;
    if (lenSq2 <= EPSILON) {
        invLen2 = 0.0f;
    } else {
        invLen2 = ONE / sqrtf(lenSq2);
    }
    float ux = cross1_x * invLen2;
    float uy = cross1_y * invLen2;
    float uz = cross1_z * invLen2;
    float uw = cross1_w * invLen2;

    // Scale to ONE (unit length)
    ux *= ONE;
    uy *= ONE;
    uz *= ONE;
    uw *= ONE;

    // Store first row (indices 0-3)
    this[0] = ux;
    this[1] = uy;
    this[2] = uz;
    this[3] = uw;

    // Compute second cross product: (ux, uy, uz, uw) × (nx, ny, nz, nw)
    float cross2_x = uz * ny - uy * nz;
    float cross2_y = ux * nz - uz * nx;
    float cross2_z = uy * nx - ux * ny;
    float cross2_w = uw * nw - uw * nw; // always 0

    // Store second row (indices 4-7)
    this[4] = cross2_x;
    this[5] = cross2_y;
    this[6] = cross2_z;
    this[7] = cross2_w;
}