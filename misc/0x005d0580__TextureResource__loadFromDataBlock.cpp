// FUNC_NAME: TextureResource::loadFromDataBlock
void TextureResource::loadFromDataBlock(int *thisPtr, uint32_t *dataBlock) {
    // dataBlock[0] is the resource type identifier
    uint32_t blockType = dataBlock[0];
    uint32_t *outputPtr = nullptr;

    // Get a resource ID from the type (likely texture allocation)
    uint32_t resourceId = resourceManager->getResourceId(blockType, &outputPtr);
    int *nativePtr = (int *)*thisPtr;
    *(uint32_t *)(nativePtr + 4) = resourceId;

    // If the output pointer indicates a special resource (value == 1), mark as system resource
    if (outputPtr == (uint32_t *)0x1) {
        *(uint32_t *)(nativePtr + 4) = resourceId | 0xf000000;
    }

    // Parse flags from dataBlock[0x18] (index 24)
    *(uint32_t *)(nativePtr + 0x28) = dataBlock[0x18] & 0x17f006;

    // Handle optional string (shader / filename)
    char *shaderName = (char *)dataBlock[0x17];
    if (shaderName != nullptr && *shaderName != '\0') {
        int shaderResults[3] = {0, 0, 0};
        code *shaderFunc = nullptr;
        // Call virtual function on a global object (likely shader manager)
        (**(code **)(**(int **)(DAT_012234f0 + 0x2c) + 4))(shaderName, shaderResults);
        // Set the shader on the native resource
        system->setShader(nativePtr + 0x2c);
        if (shaderResults[0] != 0) {
            (*shaderFunc)(shaderResults[0]);
        }
    }

    // Copy raw fields from dataBlock into the wrapper (thisPtr)
    thisPtr[1] = dataBlock[1];
    thisPtr[2] = dataBlock[2];
    thisPtr[3] = dataBlock[3];
    thisPtr[4] = dataBlock[4];

    // Byte-swap color value using lookup table (handles endianness)
    uint32_t rawColor = dataBlock[0xd];
    thisPtr[5] = ((byteSwapTable[rawColor >> 16 & 0xff] << 8 | byteSwapTable[rawColor >> 8 & 0xff]) << 8 |
                  byteSwapTable[rawColor & 0xff]) | (rawColor & 0xff000000);

    // Store texture flags from dataBlock[0x18]
    thisPtr[6] = dataBlock[0x18] & 0x80fff;
    if (dataBlock[0x11] != 0) {
        thisPtr[6] = (dataBlock[0x18] & 0x80fff) | 0x80;
    }

    // Calculate scaling factors for the texture region
    float scale = DEFAULT_SCALE; // = 1.0f (default)
    float fullTextureSize = (float)dataBlock[0x14];

    // If block type is special and full texture size is small or flags indicate special, use a smaller scale
    if (outputPtr == (uint32_t *)0x1 &&
        (fullTextureSize <= MAX_SIZE || (*(uint32_t *)(nativePtr + 0x28) & 0xe000) != 0)) {
        scale = MIN_SCALE; // = ~64.0f? (unknown)
    }

    // If the texture has special flags or its dimensions are too large, reset to default scale
    if (((*(uint32_t *)(nativePtr + 0x28) & 0xe000) != 0 || (dataBlock[0x18] & 0x80000) != 0) &&
        LARGE_THRESHOLD < fullTextureSize) {
        scale = DEFAULT_SCALE;
    }

    float left = (float)dataBlock[2];
    float top = (float)dataBlock[1];
    float right = (float)dataBlock[3];
    float bottom = (float)dataBlock[4];

    float width = (right - left) * scale;      // Scaled region width
    float height = (bottom - top) * scale;     // Scaled region height

    float clampedWidth = width;
    if ((float)(MAX_DIMENSION - 1) < width) {
        scale = ((float)(MAX_DIMENSION - 1) / width) * scale;
        clampedWidth = (float)(MAX_DIMENSION - 1);
    }

    float scaledFullWidth = fullTextureSize * scale;
    if (HALF_SIZE_THRESHOLD <= fullTextureSize) {
        scaledFullWidth = scaledFullWidth * HALF_SCALE;
    }

    float invScale = DEFAULT_SCALE / scale;

    // Write computed values to native resource
    *(float *)(nativePtr + 8) = scaledFullWidth;        // +0x08: Display width (scaled)
    *(float *)(nativePtr + 0xc) = invScale;             // +0x0c: Inverse scale
    *(int *)(nativePtr + 0x10) = (int)(height);         // +0x10: Scaled height (int)
    *(int *)(nativePtr + 0x14) = (int)clampedWidth;     // +0x14: Scaled width (int)

    // Determine filter mode (if "b" field is zero, apply default modes)
    if (dataBlock[0xb] == 0) {
        if (dataBlock[5] == 1) {
            *(uint32_t *)(nativePtr + 0x18) = 0;
            thisPtr[6] |= 2;
            *(uint32_t *)(nativePtr + 0x28) |= 2;
            goto storeFields;
        }
        if (dataBlock[5] == 2) {
            *(uint32_t *)(nativePtr + 0x18) = 0;
            thisPtr[6] |= 4;
            *(uint32_t *)(nativePtr + 0x28) |= 4;
            goto storeFields;
        }
    }
    *(uint32_t *)(nativePtr + 0x18) = dataBlock[5];

storeFields:
    *(uint32_t *)(nativePtr + 0x1c) = dataBlock[0xc];
    *(uint32_t *)(nativePtr + 0x20) = dataBlock[0x15];
    *(uint32_t *)(nativePtr + 0x24) = dataBlock[0xb];
}