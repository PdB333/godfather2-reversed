// FUNC_NAME: Animation::ensureQuaternionSequenceConsistency
void Animation::ensureQuaternionSequenceConsistency(void)
// Function address: 0x0057cc40
// Purpose: Ensure that consecutive quaternion keys in an animation sequence have positive dot product
// to avoid orientation flips during interpolation. Operates on a global quaternion array at DAT_01223d40.
// Parameter in_EAX: number of 16-byte quaternion slots in the array (each slot = 4 floats).
// The array structure: first 6 floats (0x18 bytes) are skipped (header/metadata), then a sequence of quaternions.
{
    float *baseFloat = reinterpret_cast<float*>(&DAT_01223d40);
    float *endPtr = baseFloat + in_EAX * 4; // end address derived from parameter
    float *currentPtr = baseFloat + 6; // start at first quaternion after the header

    // Skip if parameter is zero (empty sequence)
    if (endPtr != baseFloat) {
        // Process consecutive pairs: currentPtr points to the second quaternion of the pair.
        // The first quaternion of the pair is at currentPtr - 6.
        while (currentPtr + 10 != endPtr) {
            // Compute dot product between first quaternion (indices -6 to -3) and second quaternion (indices -2 to 1)
            float dot = currentPtr[-5] * currentPtr[-1] +
                        currentPtr[-3] * currentPtr[1] +
                        currentPtr[-6] * currentPtr[-2] +
                        currentPtr[-4] * currentPtr[0];
            // If dot product is negative, negate the second quaternion to keep them in the same hemisphere
            if (dot < 0.0f) {
                currentPtr[-2] = -currentPtr[-2];
                currentPtr[-1] = -currentPtr[-1];
                currentPtr[0]  = -currentPtr[0];
                currentPtr[1]  = -currentPtr[1];
            }
            // Advance by one quaternion (4 floats)
            float *nextPtr = currentPtr + 10;
            currentPtr += 4; // step by 4 floats (one quaternion)
            if (nextPtr == endPtr) break; // loop condition check
        }
    }
}