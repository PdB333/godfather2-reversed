// FUNC_NAME: MathUtils::projectVectorOnPlane
int MathUtils::projectVectorOnPlane(float* vector, float* planeNormal, float* result)
{
    float nx = planeNormal[1];
    float ny = planeNormal[0];
    float nz = planeNormal[2];
    float dot = ny * ny + nx * nx + nz * nz;
    
    // Check if plane normal is non-zero (using some global threshold)
    if (DAT_00e44598 < (float)((uint)dot & DAT_00e44680)) {
        float w = result[3]; // Preserve original w component
        float t = (vector[1] * nx + vector[2] * nz + vector[0] * ny) / dot;
        
        // Compute projection onto plane normal
        nx = planeNormal[1];
        ny = planeNormal[2];
        nz = planeNormal[3];
        result[0] = t * planeNormal[0];
        result[1] = t * nx;
        result[2] = t * ny;
        result[3] = t * nz;
        result[3] = w; // Restore w
        
        // Subtract projection to get component perpendicular to normal
        float vx = vector[1];
        float vy = vector[2];
        float vz = vector[3];
        result[0] = vector[0] - result[0];
        result[1] = vx - result[1];
        result[2] = vy - result[2];
        result[3] = vz - result[3];
        result[3] = w; // Restore w again
        
        return 1; // Success
    }
    
    // Zero normal vector - return zero vector
    result[2] = 0.0f;
    result[1] = 0.0f;
    result[0] = 0.0f;
    result[2] = 0.0f;
    result[1] = 0.0f;
    result[0] = 0.0f;
    return 0; // Failure
}