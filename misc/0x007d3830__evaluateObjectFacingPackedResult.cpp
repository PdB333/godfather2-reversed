// FUNC_NAME: evaluateObjectFacingPackedResult
int evaluateObjectFacingPackedResult(void)
{
    // Get pointers to two objects (likely transforms/matrices)
    // FUN_00471610 is likely getObjectTransform() or similar
    void* objectA = getObjectTransform();  // Returns pointer to a matrix struct
    void* objectB = getObjectTransform();

    // Extract forward vectors (or direction vectors) at offsets +0x10, +0x14, +0x18
    // These offsets typically correspond to the z-axis (forward) of a 4x3/4x4 matrix
    float dotProduct = *(float*)(objectB + 0x10) * *(float*)(objectA + 0x10) +
                       *(float*)(objectB + 0x14) * *(float*)(objectA + 0x14) +
                       *(float*)(objectB + 0x18) * *(float*)(objectA + 0x18);

    // Pack a 24-bit identifier from objectB's forward vector address
    // Shift by 8 to discard low byte, effectively using high 24 bits as ID
    uint32_t packedId = ((uint32_t)(objectB + 0x10) >> 8) & 0x00FFFFFF;

    int result;
    if (dotProduct < g_facingDotThreshold) // _DAT_00d6ef64
    {
        // Not facing: return packed ID without flag
        result = packedId << 8;
    }
    else
    {
        // Facing: set low byte to 1 as flag
        result = (packedId << 8) | 0x01;
    }

    return result;
}