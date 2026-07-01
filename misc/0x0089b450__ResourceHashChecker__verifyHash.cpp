// FUNC_NAME: ResourceHashChecker::verifyHash
void __thiscall ResourceHashChecker::verifyHash(void* thisPtr, undefined8* outputData)
{
    bool bMatch;
    bool bFinalMatch;
    int* hashPtr;
    int tempPtr1;
    int cleanupPtr;
    byte hashBuffer1[16]; // Actually 16 bytes: local_50 + uStack_4c + local_48? We'll treat as array
    byte hashBuffer2[36]; // local_40, 36 bytes buffer for second hash
    int local_1c;
    int local_4;

    bMatch = false;
    local_4 = 0;

    // First hash key
    setHashKey("XRIZZER690_C9018F8_6747557_v3");
    hashPtr = (int*)getHashFromKey(hashBuffer1);
    if ((*(int*)((int)thisPtr + 0x20) != hashPtr[0]) ||
        (*(int*)((int)thisPtr + 0x24) != hashPtr[1]) ||
        (*(int*)((int)thisPtr + 0x28) != hashPtr[2]) ||
        (*(int*)((int)thisPtr + 0x2c) != hashPtr[3])) {
        bMatch = true;
        local_1c = 0;

        // Second hash key
        setHashKey("XRODRIGUEZ_C93948C_643A487_v3");
        hashPtr = (int*)getHashFromKey(hashBuffer2);
        if ((*(int*)((int)thisPtr + 0x20) != hashPtr[0]) ||
            (*(int*)((int)thisPtr + 0x24) != hashPtr[1]) ||
            (*(int*)((int)thisPtr + 0x28) != hashPtr[2]) ||
            (*(int*)((int)thisPtr + 0x2c) != hashPtr[3])) {
            bFinalMatch = false;
            goto cleanup;
        }
    }
    bFinalMatch = true;

cleanup:
    tempPtr1 = local_1c;
    if (bMatch && (local_1c != 0)) {
        releaseHashContext();
        freeHashBuffer(tempPtr1);
    }
    cleanupPtr = local_4;
    if (local_4 != 0) {
        releaseHashContext();
        freeHashBuffer(cleanupPtr);
    }

    if (!bFinalMatch) {
        copyHashOutput(outputData);
        return;
    }

    // On match, copy constructed output
    int outputPart1 = *(int*)(outputData + 1);
    int constructedOutput = *(int*)outputData | (g_globalHashValue << 32);
    copyHashOutput(&constructedOutput);
    return;
}