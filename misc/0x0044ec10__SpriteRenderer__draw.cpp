// FUNC_NAME: SpriteRenderer::draw

void SpriteRenderer::draw(float *inputVector) {
    // Constants for fast float-to-int truncation (magic numbers for rounding toward zero)
    uint32_t magicMask1 = DAT_00e44564;
    uint32_t magicMask2 = DAT_00e44648;
    uint32_t signFix = DAT_00e2b1a4; // Possibly 0x80000000 for sign handling

    // Size of the render target (square)
    int size = *(int *)(this + 0x14);

    // Scale factor from input vector
    float scaleX = *(float *)(this + 0x1c) * inputVector[0];
    float scaleZ = *(float *)(this + 0x1c) * inputVector[2]; // Note: inputVector[1] not used

    // Fast truncation of scaleX toward zero
    float truncScaleX = (float)(magicMask2 | (magicMask1 & (uint32_t)scaleX));
    truncScaleX = (scaleX + truncScaleX) - truncScaleX;

    // Adjust for rounding errors (sign handling)
    float adjustedX = truncScaleX - (float)(-(uint32_t)((float)(magicMask1 & (uint32_t)scaleX) < truncScaleX - scaleX) & signFix);

    // Compute screen-space X center
    int screenX = (int)adjustedX - size / 2;

    // Similarly for Z (Y in screen space?)
    float truncScaleZ = (float)(magicMask2 | (magicMask1 & (uint32_t)scaleZ));
    truncScaleZ = (scaleZ + truncScaleZ) - truncScaleZ;
    float adjustedZ = truncScaleZ - (float)(-(uint32_t)((float)(magicMask1 & (uint32_t)scaleZ) < truncScaleZ - scaleZ) & signFix);
    int screenZ = (int)adjustedZ - size / 2;

    // Store screen position
    *(int *)(this + 0x20) = screenX;
    *(int *)(this + 0x24) = screenZ;

    // Clear the color buffer (RGBA, 32-bit per pixel)
    _memset(*(void **)(this + 0x34), 0, size * size * 4);

    // Copy source texture info (e.g., offset into texture atlas)
    *(int *)(this + 0x30) = *(int *)(this + 0x28);

    // Get global engine data (FS segment: TIB or static base)
    int *globalData = *(int **)((int)__readfsdword(0x2c)); // Thread Information Block?
    int basePtr = *(int *)(globalData + 8); // +0x8: pointer to main game state

    // Index into per-type arrays
    int typeIndex = *(int *)(this + 0x68);

    // Loop through first primitive list (size 0x40 per entry)
    uint32_t count1 = *(uint32_t *)(basePtr + 0x14120 + typeIndex);
    int offset1 = 0;
    for (uint32_t i = 0; i < count1; i++) {
        FUN_0044ea10(offset1 + basePtr + 0x4120 + typeIndex); // Draw primitive at this address
        offset1 += 0x40;
    }

    // Loop through second primitive list (size 0x40 per entry) – these have bounding box info
    uint32_t count2 = *(uint32_t *)(basePtr + 0x4110 + typeIndex);
    int offset2 = 0;
    int entryIdx = 0;
    for (uint32_t i = 0; i < count2; i++) {
        int *entry = (int *)(offset2 + basePtr + 0x110 + typeIndex); // Each entry at 0x40 stride
        // Pointers to vertex and radius data
        int vertexPtr = *(int *)(entry[0] + 0x18);
        float *vertexData = (float *)(basePtr + 0x30 + vertexPtr);
        float radiusData = *(float *)(basePtr + 0x70 + vertexPtr);

        // Extract vertex coordinates (position)
        float vx = vertexData[0];
        float vy = vertexData[1];
        float vz = vertexData[2];

        // Store integer coordinates in the entry
        entry[4] = (int)vx;   // minX?
        entry[5] = (int)vy;   // minY?
        entry[6] = (int)vz;   // minZ?
        entry[7] = 0;         // padding
        entry[1] = (int)radiusData; // radius? or half-extent?

        // Compute AABB corners (max = center + radius, min = center - radius)
        entry[0xc] = (int)(radiusData + vx);
        entry[0xd] = (int)(radiusData + vy);
        entry[0xe] = (int)(radiusData + vz);
        entry[0xf] = 0;

        entry[8] = (int)(vx - radiusData);
        entry[9] = (int)(vy - radiusData);
        entry[10] = (int)(vz - radiusData);
        entry[0xb] = 0;

        // Draw the primitive (likely a bounding box or sprite)
        FUN_0044ea10(entry);

        // Update base pointer (may change after call?)
        basePtr = *(int *)(globalData + 8);
        entryIdx++;
        offset2 += 0x40;
    }
    return;
}