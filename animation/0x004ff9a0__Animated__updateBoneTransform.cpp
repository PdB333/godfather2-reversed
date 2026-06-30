// FUNC_NAME: Animated::updateBoneTransform
void __thiscall Animated::updateBoneTransform(void) {
    // this pointer is param_1
    // +0x28: pointer to output destination (e.g., renderable bone buffer)
    // +0x24: pointer to animation data (with flags, translation, etc.)
    // +0x10: pointer to base of bone matrix array
    int *thisPtr = (int *)this;
    int *outputObj = (int *)thisPtr[0x28 / 4]; // +0x28
    if (outputObj == 0) {
        return;
    }

    // Access per-thread data (FS:[0x2c] -> pointer to thread-local structure)
    int *threadData = **(int ***)(__readfsdword(0x2c) + 0x2c); // double dereference
    int boneOffset = *(int *)(threadData + 2); // threadData[2] (offset +8)

    int *animData = (int *)thisPtr[0x24 / 4]; // +0x24
    float *boneMatrixBase = (float *)thisPtr[0x10 / 4]; // +0x10

    // Read bone position (4 floats) from base + 0x80 + boneOffset
    float *posPtr = boneMatrixBase + (0x80 / 4) + (boneOffset / 4);
    float posX = posPtr[0];
    float posY = posPtr[1];
    float posZ = posPtr[2];
    float posW = posPtr[3];

    // Recalculate boneOffset as absolute offset from base
    int absOffset = (int)boneMatrixBase + boneOffset;

    // Check flags at animData+0x10
    int flags = *(int *)((int)animData + 0x10);
    if ((flags & 6) == 0) {
        // Add translation from animation data (offset 0x1c,0x20,0x24)
        posX += *(float *)((int)animData + 0x1c);
        posY += *(float *)((int)animData + 0x20);
        posZ += *(float *)((int)animData + 0x24);
    }

    // Check byte at animData+0x6c
    if (*(char *)((int)animData + 0x6c) == 0) {
        // Simple path: just set position via helper function
        FUN_004e9440((int)outputObj, &posX);
        return;
    }

    // Rotation matrix (12 floats) from bone data at absOffset+0x50
    float rotMatrix[12];
    if ((flags & 0x2000) == 0) {
        // Copy rotation matrix from bone data
        float *src = (float *)(absOffset + 0x50);
        for (int i = 0; i < 12; i++) {
            rotMatrix[i] = src[i];
        }
    } else {
        // Alternative computation (e.g., from quaternion)
        FUN_004fef50();
    }

    // Write final bone transform (rotation + position) to output buffer
    if (outputObj != 0) {
        int *destBase = (int *)outputObj[0x18 / 4]; // outputObj->+0x18
        int destOffset = *(int *)(threadData + 2); // same boneOffset
        float *dest = (float *)((int)destBase + destOffset);
        // Write 12 rotation floats
        for (int i = 0; i < 12; i++) {
            dest[i] = rotMatrix[i];
        }
        // Write 4 position floats
        dest[12] = posX;
        dest[13] = posY;
        dest[14] = posZ;
        dest[15] = posW;
    }
}