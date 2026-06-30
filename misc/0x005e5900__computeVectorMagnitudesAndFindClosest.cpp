// FUNC_NAME: computeVectorMagnitudesAndFindClosest
// Address: 0x005e5900
// This function calculates the Euclidean magnitude of each vector in an array,
// stores the magnitudes in the provided output buffer, and returns the index of
// the vector with the smallest magnitude. The input array is passed via ESI,
// the count via EDI, and the output buffer as a standard 32-bit parameter.
// The global constant DAT_00e2e50c is used as an initial "best distance" value,
// likely representing FLT_MAX.

uint computeVectorMagnitudesAndFindClosest(float* outMagnitudes, const float* vectors, uint count)
{
    uint minIndex = 0;

    // If the vector array is null or the count is zero, return index 0.
    if (vectors == 0 || count == 0)
    {
        return 0;
    }

    float bestDistance = DAT_00e2e50c; // +0x00e2e50c: large initial distance (e.g., FLT_MAX)
    uint i = 0;

    do {
        // Each vector occupies 12 bytes (3 floats: x, y, z)
        float x = vectors[i * 3 + 0];
        float y = vectors[i * 3 + 1];
        float z = vectors[i * 3 + 2];
        float magnitude = sqrtf(x * x + y * y + z * z);

        outMagnitudes[i] = magnitude;

        if (magnitude < bestDistance)
        {
            minIndex = i;
            bestDistance = magnitude;
        }

        i++;
    } while (i < count);

    return minIndex;
}