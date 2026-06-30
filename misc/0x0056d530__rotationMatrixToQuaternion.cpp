// FUNC_NAME: rotationMatrixToQuaternion
// Function address: 0x0056d530
// Converts a 3x3 rotation matrix (stored in a 4x4 matrix, using indices 0,1,2,4,5,6,8,9,10) to a quaternion (x,y,z,w).
// Standard algorithm: if 1 + trace > 0, use that branch; otherwise pick largest diagonal element.

#define ONE_PLUS_EPSILON 1.0f
#define HALF 0.5f

void rotationMatrixToQuaternion(float *matrix, float *quat)
{
    float tempQuat[4];
    int indices[3] = {1, 2, 0};
    float trace = matrix[0] + matrix[5] + matrix[10]; // m00 + m11 + m22

    if (trace + ONE_PLUS_EPSILON > 0.0f) // 1 + trace > 0
    {
        float s = sqrtf(trace + ONE_PLUS_EPSILON); // sqrt(1 + trace)
        quat[3] = s * HALF; // qw
        float invS = HALF / s;
        quat[0] = (matrix[6] - matrix[9]) * invS; // (m12 - m21)
        quat[1] = (matrix[8] - matrix[2]) * invS; // (m20 - m02)
        quat[2] = (matrix[1] - matrix[4]) * invS; // (m01 - m10)
    }
    else
    {
        // Determine the largest diagonal element
        unsigned largestIdx = (matrix[0] < matrix[5]) ? 0 : 1; // max(m00, m11)
        if (matrix[largestIdx * 5] <= matrix[10] && matrix[largestIdx * 5] != matrix[10])
        {
            largestIdx = 2; // m22 is largest
        }

        int nextIdx = indices[largestIdx];
        int thirdIdx = indices[nextIdx];

        float s = sqrtf(matrix[largestIdx * 5] - (matrix[nextIdx * 5] + matrix[thirdIdx * 5]) + ONE_PLUS_EPSILON);
        tempQuat[largestIdx] = s * HALF;
        if (s != 0.0f)
        {
            s = HALF / s;
        }
        tempQuat[3] = (matrix[thirdIdx + nextIdx * 4] - matrix[nextIdx + thirdIdx * 4]) * s;
        tempQuat[nextIdx] = (matrix[largestIdx + nextIdx * 4] + matrix[nextIdx + largestIdx * 4]) * s;
        tempQuat[thirdIdx] = (matrix[largestIdx + thirdIdx * 4] + matrix[thirdIdx + largestIdx * 4]) * s;

        quat[0] = tempQuat[0];
        quat[1] = tempQuat[1];
        quat[2] = tempQuat[2];
        quat[3] = tempQuat[3];
    }
}