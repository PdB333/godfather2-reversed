// FUNC_NAME: transformVectorArray
// Function at 0x00720980: Applies a transformation to an array of 3D vectors.
// Input: inArray (float3*), count (int), outArray (float3*), transformData (some matrix/context pointer)
// Output: returns outArray pointer.
// Uses a global constant _DAT_00d5780c (likely a transformation matrix or vector).
// Note: The decompilation shows a redundant local_24 = _DAT_00d5780c that is not used; possibly optimized out.
// The underlying function FUN_0056b420 performs per-vector transformation.

float* __cdecl transformVectorArray(float* outArray, float* inArray, int count, void* transformData)
{
    int i;
    float src[3];
    float dst[3];
    float globalConst = *(float*)0x00d5780c; // Global transformation constant

    if (count > 0)
    {
        float* srcPtr = inArray;
        float* dstPtr = outArray;
        for (i = 0; i < count; i++)
        {
            // Read three floats from input (a 12-byte vector)
            src[0] = srcPtr[0];
            src[1] = srcPtr[1];
            src[2] = srcPtr[2];

            // Apply transformation (likely affine or linear mapping)
            // FUN_0056b420 (transformation function) takes transformData, input, output
            // Possibly also uses globalConst internally?
            FUN_0056b420(transformData, src, dst);

            // Write three floats to output (12 bytes)
            dstPtr[0] = dst[0];
            dstPtr[1] = dst[1];
            // Third component written at offset 8 from current output element
            // Equivalent to dstPtr[2] = dst[2]
            *(float*)((uintptr_t)outArray - (uintptr_t)inArray + (uintptr_t)srcPtr) = dst[2];

            srcPtr += 3; // Advance by 3 floats (12 bytes)
            dstPtr += 3;
        }
    }

    return outArray;
}