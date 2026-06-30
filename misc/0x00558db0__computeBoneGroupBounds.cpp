// FUNC_NAME: computeBoneGroupBounds

extern float g_positiveInfinity;    // DAT_00e2e50c
extern float g_negativeInfinity;    // DAT_00e44758
extern float g_scaleFactor;         // DAT_00e2cd54
extern float g_wComponent;          // DAT_00e2b1a4 (likely 1.0f)
extern void updateBoundingBox(float* box); // FUN_00a66880

void computeBoneGroupBounds(float* outCenter, const uint8_t* boneIndices, void* skeleton)
{
    float minX = g_positiveInfinity;
    float minY = g_positiveInfinity;
    float minZ = g_positiveInfinity;
    float minW = g_positiveInfinity;

    float maxX = g_negativeInfinity;
    float maxY = g_negativeInfinity;
    float maxZ = g_negativeInfinity;
    float maxW = g_negativeInfinity;

    float scale = g_scaleFactor;

    while (*boneIndices) {
        int index = (*boneIndices) * 4;
        float point[4];
        // virtual call to skeleton->getBoneWorldPosition(index, point)
        (*(void (__thiscall**)(void*, float*, int*))(*((int*)skeleton) + 0xa4))(skeleton, point, &index);

        float x = point[0];
        float y = point[1];
        float z = point[2];
        float w = point[3]; // likely 1.0

        if (x < minX) minX = x;
        if (y < minY) minY = y;
        if (z < minZ) minZ = z;
        if (w > minW) minW = w; // note reversed logic for w

        if (x > maxX) maxX = x;
        if (y > maxY) maxY = y;
        if (z > maxZ) maxZ = z;
        if (w < maxW) maxW = w;

        boneIndices++;
    }

    // Compute center
    outCenter[0] = (maxX + minX) * scale; // center X
    outCenter[2] = (maxZ + minZ) * scale; // center Z
    outCenter[1] = (maxY + minY) * scale; // center Y
    outCenter[3] = (maxW + minW) * scale; // center W (likely homogeneous)

    float offset = *(float*)(boneIndices - 1 + 0xc); // note: boneIndices has advanced, but original param_2+0xc
    // Original param_2 is saved? Actually we lost original pointer. In the decompiled code, after loop, iVar4 points to end of string.
    // They used param_2+0xc which is a float from the original structure. We need to keep original param_2.
    // So we need to store original pointer. We'll fix.

    // Better: store original boneIndicesBase.
}

// Corrected version with preserved original pointer:
void computeBoneGroupBounds(float* outCenter, const uint8_t* boneIndices, void* skeleton)
{
    const uint8_t* originalBoneIndices = boneIndices;
    float minX = g_positiveInfinity;
    float minY = g_positiveInfinity;
    float minZ = g_positiveInfinity;
    float minW = g_positiveInfinity;

    float maxX = g_negativeInfinity;
    float maxY = g_negativeInfinity;
    float maxZ = g_negativeInfinity;
    float maxW = g_negativeInfinity;

    float scale = g_scaleFactor;

    while (*boneIndices) {
        int index = (*boneIndices) * 4;
        float point[4];
        (*(void (__thiscall**)(void*, float*, int*))(*((int*)skeleton) + 0xa4))(skeleton, point, &index);

        float x = point[0];
        float y = point[1];
        float z = point[2];
        float w = point[3];

        if (x < minX) minX = x;
        if (y < minY) minY = y;
        if (z < minZ) minZ = z;
        if (g_wComponent <= w) minW = g_wComponent; // note: it sets minW to g_wComponent if g_wComponent <= w, else keeps minW

        if (x > maxX) maxX = x;
        if (y > maxY) maxY = y;
        if (z > maxZ) maxZ = z;
        if (w <= g_wComponent) maxW = g_wComponent;

        boneIndices++;
    }

    outCenter[0] = (maxX + minX) * scale;
    outCenter[2] = (maxZ + minZ) * scale;
    outCenter[1] = (maxY + minY) * scale;
    outCenter[3] = (maxW + minW) * scale;

    float offset = *(float*)(originalBoneIndices + 0xc); // +0x0c is a float field

    float adjustedX = (maxX - outCenter[0]) + offset;
    float adjustedY = (maxY - outCenter[1]) + offset;
    float adjustedZ = (maxZ - outCenter[2]) + offset;
    float adjustedW = (maxW - outCenter[3]) + offset;

    float box[4] = { adjustedX, adjustedY, adjustedZ, adjustedW };
    updateBoundingBox(box);
}