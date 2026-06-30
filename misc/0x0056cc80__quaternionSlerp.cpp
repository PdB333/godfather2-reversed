// FUNC_NAME: quaternionSlerp

/**
 * Address: 0x0056cc80
 * Role: Spherical linear interpolation (slerp) for quaternions with fallback to linear interpolation when the angle is small.
 * Interpolates between two quaternions (param_2 and param_3) by factor param_1.
 * Output stored in param_4. Uses param_5 as an epsilon threshold to decide when to use lerp.
 */
void quaternionSlerp(float t, float* q1, float* q2, float* result, float epsilon)
{
    float dot = q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];
    
    float q2x, q2y, q2z, q2w;
    if (dot >= 0.0f) {
        q2x = q2[0];
        q2y = q2[1];
        q2z = q2[2];
        q2w = q2[3];
    } else {
        // Negate target quaternion to take the shortest path
        dot = -dot; // Equivalent to 0.0 - dot
        q2x = -q2[0];
        q2y = -q2[1];
        q2z = -q2[2];
        q2w = -q2[3];
    }

    float a, b;
    if (1.0f - dot <= epsilon) {
        // Angle is small, use linear interpolation
        a = 1.0f - t;
        b = t;
    } else {
        // Standard slerp calculation
        float theta = acosf(dot);
        float sinTheta = sinf(theta);
        float scale = 1.0f / sinTheta;

        a = sinf((1.0f - t) * theta) * scale;
        b = sinf(t * theta) * scale;
    }

    result[0] = a * q1[0] + b * q2x;
    result[1] = a * q1[1] + b * q2y;
    result[2] = a * q1[2] + b * q2z;
    result[3] = a * q1[3] + b * q2w;
}