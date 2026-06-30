// FUNC_NAME: matrix4x4ToQuaternion
// Address: 0x0056d530
// Converts a 4x4 homogeneous transformation matrix (row-major) to a quaternion (w,x,y,z)
void matrix4x4ToQuaternion(const float mat[16], float quat[4])
{
    static const float kTraceAdd = 1.0f; // DAT_00e2b1a4 – adds 1 to trace for sqrt
    static const float kHalf = 0.5f;     // DAT_00e2cd54 – scalar factor (0.5)

    float trace = mat[0] + mat[5] + mat[10]; // m00 + m11 + m22

    if (trace > 0.0f)
    {
        // Standard formula: w = sqrt(trace+1)*0.5, axis = (m12-m21, m20-m02, m01-m10) / (2*sqrt(trace+1))
        float s = sqrtf(trace + kTraceAdd);
        float recip = kHalf / s;
        quat[3] = s * kHalf;                   // w
        quat[0] = (mat[6] - mat[9]) * recip;   // (m12 - m21) / (2*s)
        quat[1] = (mat[8] - mat[2]) * recip;   // (m20 - m02) / (2*s)
        quat[2] = (mat[1] - mat[4]) * recip;   // (m01 - m10) / (2*s)
        return;
    }

    // Permutation table for selecting the largest diagonal component
    int perm[3] = {1, 2, 0}; // next index after largest
    int largestIdx = (mat[0] < mat[5]) ? 1 : 0; // compare m00 and m11
    if (mat[largestIdx * 5] <= mat[10] && mat[10] != mat[largestIdx * 5])
    {
        largestIdx = 2; // m22 is largest
    }

    int nextIdx = perm[largestIdx];
    int nextNextIdx = perm[nextIdx];

    // s = sqrt(1 + m[largest][largest] - m[next][next] - m[nextNext][nextNext])
    float s = sqrtf((mat[largestIdx * 5] - (mat[nextNextIdx * 5] + mat[nextIdx * 5])) + kTraceAdd);
    quat[largestIdx] = s * kHalf; // component corresponding to largest diagonal

    float recip = kHalf / s;
    // Off-diagonal differences and sums
    quat[3] = (mat[nextIdx + nextNextIdx * 4] - mat[nextNextIdx + nextIdx * 4]) * recip; // w-like term
    quat[nextIdx] = (mat[largestIdx + nextIdx * 4] + mat[nextIdx + largestIdx * 4]) * recip;
    quat[nextNextIdx] = (mat[largestIdx + nextNextIdx * 4] + mat[nextNextIdx + largestIdx * 4]) * recip;
}