// FUNC_NAME: MathUtils::normalizeVector3D
// Return value: 1 if successful (non-zero length), 0 if zero-length vector
// param_1: vecOut (output normalized vector)
// param_2: vecIn (input vector to normalize)
// param_3: outLength (optional, stores original length if normalization was successful)
int MathUtils::normalizeVector3D(float* vecOut, const float* vecIn, float* outLength)
{
    float x = vecIn[0];
    float y = vecIn[1];
    float z = vecIn[2];
    
    // Compute squared length
    float lengthSq = x * x + y * y + z * z;
    
    float invLength;
    float length;
    
    // Check against epsilon (DAT_00e2cbe0 is likely a small epsilon, possibly 0.0 or ~1.175e-38)
    if (lengthSq <= 0.0f) {
        length = 0.0f;
        invLength = 0.0f;
    }
    else {
        length = sqrtf(lengthSq);
        // DAT_00e2b1a4 = 1.0f (the constant 1.0 used to compute reciprocal)
        invLength = 1.0f / length;
    }
    
    // Write normalized components
    vecOut[0] = invLength * x;
    vecOut[1] = invLength * y;
    vecOut[2] = invLength * z;
    
    // Return success indicator
    if (length > 0.0f) {
        if (outLength != nullptr) {
            *outLength = length;
        }
        return 1; // Success
    }
    return 0; // Failed (zero-length input)
}