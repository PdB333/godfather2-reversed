// FUN_00419370: quaternionToTransformationMatrix
void __fastcall quaternionToTransformationMatrix(float* outMatrix, const QuaternionTransform* in)
{
    float squaredLen;
    float normFactor;
    float qx, qy, qz, qw;
    float right_x, right_y, right_z, right_w;
    float up_x, up_y, up_z, up_w;
    float forward_x, forward_y, forward_z, forward_w;
    float dotScale;
    float lenSq;

    // Global constants (inferred from references)
    static const float kZeroThreshold = 0.0f;  // DAT_00e2cbe0 - threshold for quaternion length check
    static const float kOne = 1.0f;           // DAT_00e2b1a4 - normalization factor (assumed 1.0)
    static const float kSingularityMax = 0.999f; // DAT_00e2fc44 - upper bound for singularity detection
    static const float kSingularityMin = -0.999f; // DAT_00e448a0 - lower bound for singularity detection

    // Read quaternion from input (offsets 0x20, 0x24, 0x28, 0x2c)
    qx = *(float*)((int)in + 0x20);
    qy = *(float*)((int)in + 0x24);
    qz = *(float*)((int)in + 0x28);
    qw = *(float*)((int)in + 0x2c);

    // Normalize the quaternion
    squaredLen = qx*qx + qy*qy + qz*qz + qw*qw;
    if (squaredLen <= kZeroThreshold) {
        normFactor = 0.0f;
    } else {
        normFactor = kOne / sqrtf(squaredLen);
    }
    outMatrix[8] = qx * normFactor;  // output[8..11] stores normalized quaternion (third column)
    outMatrix[9] = qy * normFactor;
    outMatrix[10] = qz * normFactor;
    outMatrix[11] = qw * normFactor;

    // Compute initial right vector as cross product of (0,1,0) with normalized quaternion's imaginary part
    // right = cross(up, forward) where up = (0,1,0), forward = (qx_norm, qy_norm, qz_norm)
    // Actually: right.x = 0*qz_norm - 1*qy_norm? No: cross(up, forward) = (up.y*forward.z - up.z*forward.y, ...)
    // Using (0,1,0) x (qx,qy,qz) = (1*qz - 0*qy, 0*qx - 0*qz, 0*qy - 1*qx) = (qz, 0, -qx)
    // But code computes: out[0] = out[9]*0 - kOne*out[10] = -qz, out[1] = out[10]*0 - out[8]*0 = 0, out[2] = kOne*out[8] - out[9]*0 = qx
    // So right = (-qz, 0, qx) which is -cross(up, forward). This is fine as long as basis is consistent.
    outMatrix[0] = -outMatrix[10];          // -qz
    outMatrix[1] = 0.0f;                    // 0
    outMatrix[2] = outMatrix[8];            // qx
    outMatrix[3] = 0.0f;                    // w component = 0

    // Check for singularity when the right vector degenerates (i.e., forward almost parallel to up)
    if ((outMatrix[0] <= kSingularityMax) && (kSingularityMin <= outMatrix[0]) &&
        (outMatrix[1] <= kSingularityMax) && (kSingularityMin <= outMatrix[1]) &&
        (outMatrix[2] <= kSingularityMax) && (kSingularityMin <= outMatrix[2])) {
        // Singularity: forward nearly aligned with up, use default basis
        outMatrix[0] = kOne;    // right = (1,0,0)
        outMatrix[1] = 0.0f;
        outMatrix[2] = 0.0f;
        outMatrix[3] = 0.0f;
        outMatrix[4] = 0.0f;   // up = (0,0,1)
        outMatrix[5] = 0.0f;
        outMatrix[6] = kOne;
        outMatrix[7] = 0.0f;
        // Translation from input (offsets 0x30, 0x34, 0x38, 0x3c)
        outMatrix[12] = *(float*)((int)in + 0x30);
        outMatrix[13] = *(float*)((int)in + 0x34);
        outMatrix[14] = *(float*)((int)in + 0x38);
        outMatrix[15] = *(float*)((int)in + 0x3c);
        return;
    }

    // Normal case: compute orthonormal basis from the right vector and forward
    // Normalize the right vector (stored in outMatrix[0..2])
    right_x = outMatrix[0];
    right_y = outMatrix[1];
    right_z = outMatrix[2];
    right_w = outMatrix[3];  // always 0
    squaredLen = right_x*right_x + right_y*right_y + right_z*right_z + right_w*right_w;
    if (squaredLen <= kZeroThreshold) {
        normFactor = 0.0f;
    } else {
        normFactor = kOne / sqrtf(squaredLen);
    }
    outMatrix[0] = right_x * normFactor;
    outMatrix[1] = right_y * normFactor;
    outMatrix[2] = right_z * normFactor;
    outMatrix[3] = right_w * normFactor;

    // Compute up vector as cross product of forward and right
    // up = cross(forward, right) where forward = (out[8], out[9], out[10])
    outMatrix[4] = outMatrix[2] * outMatrix[9] - outMatrix[1] * outMatrix[10];  // cross.z*forward.y - cross.y*forward.z? Actually this is: right_z*forward_y - right_y*forward_z
    outMatrix[5] = outMatrix[0] * outMatrix[10] - outMatrix[2] * outMatrix[8];  // right_x*forward_z - right_z*forward_x
    outMatrix[6] = outMatrix[1] * outMatrix[8] - outMatrix[0] * outMatrix[9];  // right_y*forward_x - right_x*forward_y
    outMatrix[7] = outMatrix[3] * outMatrix[11] - outMatrix[3] * outMatrix[11]; // 0

    // Normalize the up vector
    up_x = outMatrix[4];
    up_y = outMatrix[5];
    up_z = outMatrix[6];
    up_w = outMatrix[7];
    squaredLen = up_x*up_x + up_y*up_y + up_z*up_z + up_w*up_w;
    if (kZeroThreshold < squaredLen) {
        normFactor = kOne / sqrtf(squaredLen);
        outMatrix[4] = up_x * normFactor;
        outMatrix[5] = up_y * normFactor;
        outMatrix[6] = up_z * normFactor;
        outMatrix[7] = up_w * normFactor;
    } else {
        // Length is zero (should not happen), leave as zero
    }

    // Set translation from input (offsets 0x30, 0x34, 0x38, 0x3c)
    outMatrix[12] = *(float*)((int)in + 0x30);
    outMatrix[13] = *(float*)((int)in + 0x34);
    outMatrix[14] = *(float*)((int)in + 0x38);
    outMatrix[15] = *(float*)((int)in + 0x3c);
}