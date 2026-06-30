// FUNC_NAME: Math::normalizeVector
// Returns a normalized copy of the input vector. If the squared length is below an epsilon threshold, returns a zero vector.
// Input: src (3 floats via implicit EAX pointer), Output: dst (3 floats via explicit parameter)
void normalizeVector(float* dst, const float* src) 
{
    // Unpack source components
    float x = src[0];
    float y = src[1];
    float z = src[2];

    // Compute squared length
    float lenSq = x * x + y * y + z * z;

    // If length is effectively zero (below epsilon), result is zero vector
    if (lenSq <= epsilonThreshold) {
        dst[0] = 0.0f;
        dst[1] = 0.0f;
        dst[2] = 0.0f;
        return;
    }

    // Otherwise scale by 1/len (DAT_00e2b1a4 is likely 1.0f)
    float invLen = invScale / sqrtf(lenSq);   // invScale = 1.0f (commonly)
    dst[0] = x * invLen;
    dst[1] = y * invLen;
    dst[2] = z * invLen;
}