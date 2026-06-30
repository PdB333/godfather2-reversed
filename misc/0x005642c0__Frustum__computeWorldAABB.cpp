// FUNC_NAME: Frustum::computeWorldAABB

void __thiscall Frustum::computeWorldAABB(Frustum* this, undefined4 transformIndex, float nearDistance, float* outAABB)
{
    // Offset +0x50: Array of 8 float4 (frustum corners in local space, each 16 bytes)
    // Offset +0x3C: float m_nearDistance or m_splitDistance

    float tempMin[4];
    float transformedPoints[31]; // temporary array for world-space corners (size might be larger than needed)

    int cornerIndex = 0;
    float* pCorner = reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(this) + 0x50);

    // Transform all 8 frustum corners using the given transform (camera/light matrix)
    for (int i = 0; i < 8; i++)
    {
        FUN_00aa2bb0(transformIndex, pCorner); // assumes this function reads pCorner (local corner) and writes world corner to same location
        pCorner += 4; // each corner is 4 floats
    }

    // Initialize output AABB with the first corner (copied from the corner array into tempMin)
    float firstX = tempMin[0];
    float firstY = tempMin[1];
    float firstZ = tempMin[2];
    float firstW = tempMin[3];

    // Set both min and max to the first corner
    outAABB[0] = firstX; // min.x
    outAABB[1] = firstY; // min.y
    outAABB[2] = firstZ; // min.z
    outAABB[3] = firstW; // min.w (often 1.0f)
    outAABB[4] = firstX; // max.x
    outAABB[5] = firstY; // max.y
    outAABB[6] = firstZ; // max.z
    outAABB[7] = firstW; // max.w

    // Iterate over the remaining transformed corners (starting from index 2 in transformedPoints) to compute min/max
    // The pointer arithmetic jumps 4 floats per iteration, covering the rest of the array.
    float* pIter = transformedPoints + 2;  // Skip first two floats? Possibly due to alignment or extra data
    int remaining = 7; // number of additional corners to process (8 total, index 1 is at offset 4? unclear, but we do 7 iterations)

    do
    {
        float cornerX = pIter[-2];
        float cornerY = pIter[-1];
        float cornerZ = pIter[0];
        float cornerW = pIter[1];

        // Update minimum values
        if (cornerX < outAABB[0]) outAABB[0] = cornerX;
        if (cornerY < outAABB[1]) outAABB[1] = cornerY;
        if (cornerZ < outAABB[2]) outAABB[2] = cornerZ;
        if (cornerW < outAABB[3]) outAABB[3] = cornerW;

        // Update maximum values
        if (outAABB[4] < cornerX) outAABB[4] = cornerX;
        if (outAABB[5] < cornerY) outAABB[5] = cornerY;
        if (outAABB[6] < cornerZ) outAABB[6] = cornerZ;
        if (outAABB[7] < cornerW) outAABB[7] = cornerW;

        pIter += 4;
        remaining--;
    } while (remaining != 0);

    // Adjust the AABB along the view direction if the given nearDistance differs from stored near distance
    // This shifts the box to match the actual split distance (e.g., for cascaded shadow maps)
    float storedNear = *(float*)((uint8_t*)this + 0x3C);
    if (nearDistance != storedNear)
    {
        float delta = nearDistance - storedNear;

        // Widen the near (min) side and far (max) side
        outAABB[0] -= delta; // min.z or min.x? depends on convention
        outAABB[1] -= delta;
        outAABB[2] -= delta;
        // outAABB[3] remains unchanged? 
        outAABB[4] += delta;
        outAABB[5] += delta;
        outAABB[6] += delta;
        // outAABB[7] remains unchanged?
    }

    // Note: The function has minor dead stores (e.g., outAABB[3]=outAABB[3]) which are omitted.
}