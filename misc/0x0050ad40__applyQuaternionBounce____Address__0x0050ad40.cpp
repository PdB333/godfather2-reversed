// FUNC_NAME: applyQuaternionBounce // Address: 0x0050ad40
// Role: Adjusts a quaternion for bounce/reflection off a surface with material-based coefficients.
// Takes output quaternion (outQuat), surface normal (normal), object pointer (obj), and source quaternion (srcQuat).
// If the quaternion's imaginary part is opposite to the normal and its magnitude exceeds a threshold,
// it blends the quaternion with a reflected version using material-dependent coefficients.

void __fastcall applyQuaternionBounce(float *outQuat, float *normal, int obj, float *srcQuat)
{
    // Copy source quaternion to output (w, x, y, z or similar ordering)
    outQuat[0] = srcQuat[0];
    outQuat[1] = srcQuat[1];
    outQuat[2] = srcQuat[2];
    outQuat[3] = srcQuat[3];

    // Extract components for condition check
    float ny = normal[1];            // normal.y
    float nz = normal[2];            // normal.z
    float wy = outQuat[2];           // quaternion imaginary y
    float wz = outQuat[1];           // quaternion imaginary z? (order might be w,x,y,z)
    float ww = outQuat[3];           // quaternion real part? (assuming w at index 3)
    float nx = normal[0];            // normal.x

    // Condition: (ny * wz + nz * wy + ww * nx) < 0 and squared norm of (wy,wz,ww) > threshold
    if ((ny * wz + nz * wy + ww * nx >= 0.0f) ||
        (ww * ww + wz * wz + wy * wy <= DAT_00e44598))  // DAT_00e44598 is a global threshold
    {
        return;
    }

    // Compute dot product of output quaternion imaginary part with normal? Actually product of components
    float dot_x = outQuat[0] * normal[0];    // w * normal.x? (index 0 is w)
    float dot_y = outQuat[1] * normal[1];    // x? * normal.y
    float dot_z = outQuat[2] * normal[2];    // y? * normal.z

    // Fetch material coefficients from object data
    // obj+0x24 points to some structure with fields at offsets 0x155 and 0x156 (byte indices)
    int *structPtr = *(int **)(obj + 0x24);   // +0x24
    char index1 = *(char *)(structPtr + 0x155); // index into global float array
    char index2 = *(char *)(structPtr + 0x156);
    float coeff1 = *(float *)(&DAT_00e38088 + index1 * 4); // elasticity coefficient
    float coeff2 = *(float *)(&DAT_00e3809c + index2 * 4); // friction coefficient

    // Projection of the quaternion onto the normal (scaled by normal components)
    float sumDot = dot_x + dot_y + dot_z;
    float proj_x = sumDot * normal[0];
    float proj_y = sumDot * normal[1];
    float proj_z = sumDot * normal[2];

    // Blend: new = coeff2 * (old - proj) + coeff1 * proj
    outQuat[0] = coeff2 * (outQuat[0] - proj_x) + coeff1 * proj_x;
    outQuat[1] = coeff2 * (outQuat[1] - proj_y) + coeff1 * proj_y;
    outQuat[2] = coeff2 * (outQuat[2] - proj_z) + coeff1 * proj_z;
    // Note: outQuat[3] remains unchanged? The decompiled code sets it to some local stack values, but the last two lines seem to be an artifact:
    // in_EAX[3] = fStack_24 + fStack_14; in_EAX[3] = fVar3; -- this is confusing. Likely the decompiler mis-handled.
    // The original probably modifies w component based on a reflection. For now, preserve w as from source.
    // Actually the final assignment sets outQuat[3] = fVar3 (which was the original srcQuat[3] after copy). So it's unchanged.
    outQuat[3] = srcQuat[3];
}