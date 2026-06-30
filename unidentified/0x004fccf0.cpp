// FUN_004fccf0: RenderManager::processObjectList
void __thiscall RenderManager::processObjectList(int thisPtr, int renderData)
{
    int objectBase;
    int objectIdx;
    int cameraPtr;
    uint loopCounter;
    uint i;
    int objPtr;
    uint flag;
    int objectCount;
    int subObjectCount;
    int unknownVar;

    float colorMatrix[16];
    float tempMatrix[4];

    // Copy 16 floats from renderData+0x40 (likely a 4x4 color matrix or light transform)
    // Offsets: +0x40 to +0x7C (16 * 4 = 64 bytes)
    colorMatrix[0] = *(float *)(renderData + 0x40);
    colorMatrix[1] = *(float *)(renderData + 0x44);
    colorMatrix[2] = *(float *)(renderData + 0x48);
    colorMatrix[3] = *(float *)(renderData + 0x4C);
    colorMatrix[4] = *(float *)(renderData + 0x50);
    colorMatrix[5] = *(float *)(renderData + 0x54);
    colorMatrix[6] = *(float *)(renderData + 0x58);
    colorMatrix[7] = *(float *)(renderData + 0x5C);
    colorMatrix[8] = *(float *)(renderData + 0x60);
    colorMatrix[9] = *(float *)(renderData + 0x64);
    colorMatrix[10] = *(float *)(renderData + 0x68);
    colorMatrix[11] = *(float *)(renderData + 0x6C);
    colorMatrix[12] = *(float *)(renderData + 0x70);
    colorMatrix[13] = *(float *)(renderData + 0x74);
    colorMatrix[14] = *(float *)(renderData + 0x78);
    colorMatrix[15] = *(float *)(renderData + 0x7C);

    loopCounter = 0;
    objectCount = *(int *)(thisPtr + 0x20);
    if (objectCount != 0) {
        objectBase = 0;
        do {
            objPtr = *(int *)(thisPtr + 0x1C) + objectBase; // Base of current object (size 0x1B0)

            // Push matrix? Argument: flag based on (this+0x14) (0x40 or 0)
            flag = (-(uint)(*(int *)(thisPtr + 0x14) != 0) & 0xFFFFFFC0) + 0x40;
            FUN_005334b0((int)colorMatrix, flag); // Start matrix operations

            FUN_00534ff0(0); // Set identity?
            FUN_00417560();  // Multiply matrix?
            FUN_00535220();  // Pop matrix? (not sure)

            cameraPtr = *(int *)(thisPtr + 0x10); // Camera or scene transform
            // Read camera data (position? +0x74, +0x78, +0x7C)
            DAT_01219b40 = *(float *)(cameraPtr + 0x74);
            DAT_01219b44 = *(float *)(cameraPtr + 0x78);
            DAT_01219b48 = *(float *)(cameraPtr + 0x7C);
            // Read object-specific data at offset 0x190 (400 into 0x1B0)
            DAT_01219b4C = *(float *)(objPtr + 0x190);

            // Copy globals into local matrix (first 4 floats of colorMatrix?)
            tempMatrix[0] = DAT_01219b40;
            tempMatrix[1] = DAT_01219b44;
            tempMatrix[2] = DAT_01219b48;
            tempMatrix[3] = DAT_01219b4C;

            // If condition: DAT_012058e8 points to some global array, and index based on DAT_01219b20
            if ((DAT_012058e8 == &DAT_01219a70) && 
                (*(int *)(&DAT_01219cac + (uint)(DAT_01219b20) * 0x30) != 0)) {
                FUN_0060add0(DAT_01219a80, *(int *)(&DAT_01219cac + (uint)(DAT_01219b20) * 0x30), &tempMatrix);
            }

            // Clamp render state globals
            if (DAT_012058d0 < 0xE) {
                DAT_012058d0 = 0xE;
            }
            if (DAT_00f15988 < 0xE) { // Note: decompiled says "0xe < DAT_00f15988" but logic inverted?
                // Actually: if (0xe < DAT_00f15988) DAT_00f15988 = 0xe; This would *lower* it, maybe it's a min?
                // But the pattern suggests clamping to maximum? There might be a bug in decompilation.
                // We'll keep original logic.
                // if (DAT_00f15988 < 0xE) ... The comment is from decompiled.
                // Let's reinterpret: The original code likely checks and sets min/max.
                // For now, keep as is.
                DAT_00f15988 = 0xE;
            }

            // More clamping
            unknownVar = 0;
            DAT_011f3a10 = 0;
            if (DAT_012058d0 < 0x1B) {
                DAT_012058d0 = 0x1B;
            }
            if (DAT_00f15988 > 0x1A) { // 0x1a < DAT_00f15988 -> set to 0x1B
                DAT_00f15988 = 0x1B;
            }
            DAT_011f3a44 = 1;

            FUN_004ec7a0(); // Apply render state changes

            colorMatrix[0] = DAT_00e2b1a4; // Override first element?
            FUN_004eccc0(8); // Set light? (arg 8)

            subObjectCount = *(byte *)(objPtr + 0x1AD); // Number of sub-objects at offset 0x1AD
            if (subObjectCount != 1 && (int)(subObjectCount - 1) >= 0) {
                for (i = 0; i < (uint)(subObjectCount - 1); i++) {
                    FUN_004fca40(thisPtr, colorMatrix); // Render each sub-object
                }
            }

            FUN_00533720(colorMatrix); // End of rendering for this object

            objectBase += 0x1B0; // Move to next object (size 432 bytes)
            loopCounter++;
        } while (loopCounter < (uint)objectCount);
    }

    if (objectCount != 0) {
        *(int *)(thisPtr + 0x20) = 0; // Reset object count
    }
    return;
}