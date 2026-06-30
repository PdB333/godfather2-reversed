// FUNC_NAME: VFXManager::spawnRandomEffectByDirection
void __thiscall VFXManager::spawnRandomEffectByDirection(VFXManager* thisPtr, Vector4* pDirection, float probability, int minValue, int maxValue)
{
    int iVar1;
    int* pSpawnInfo;
    int iVar3;
    float randFloat;
    // [local_c, fStack_8, local_4] is a struct: likely Vector4 or some packed data
    Vector4 localVec;
    float uVar4;

    // Check if direction vector is non-zero
    if ( (pDirection->x != 0.0f || pDirection->y != 0.0f || pDirection->z != 0.0f || pDirection->w != 0.0f) &&
         ((float)rand() * RAND_FLOAT_SCALE <= probability) )
    {
        // Compute random value in range [minValue, maxValue]
        iVar1 = rand();
        randFloat = (float)iVar1 * RAND_FLOAT_SCALE;
        pSpawnInfo = (int*)getSpawnInfo(pDirection); // FUN_00800800, likely returns pointer to spawn info struct
        if (pSpawnInfo != nullptr)
        {
            // Store computed value at offset 0xA5 (e.g., lifetime or intensity)
            pSpawnInfo[0xA5] = (int)(randFloat * (float)(maxValue - minValue)) + minValue;

            // Get current physics time or timestamp from some manager
            iVar3 = getPhysicsTimeManager(); // FUN_00471610
            int* pPhysicsTime = (int*)iVar3;
            // Read 64-bit value at +0x30 and 32-bit at +0x38, compose into localVec
            localVec.w = *(float*)(pPhysicsTime + 0x38/4); // offset 0x38 as float
            uint64_t time64 = *(uint64_t*)(pPhysicsTime + 0x30/4); // +0x30
            float timeUpper = (float)(time64 >> 32); // upper 32 bits as float
            // Build localVec.x as combination of timeUpper + global offset and lower 32 bits
            localVec.x = (float)(int)(time64 & 0xFFFFFFFF); // truncate to int? Actually the code does CONCAT44
            // The original code: _local_c = CONCAT44(fStack_8 + _DAT_00d5c458,(int)*(undefined8 *)(iVar3 + 0x30));
            // That is likely: localVec.x = (float)(int)(time64 & 0xFFFFFFFF);
            // and localVec.y = fStack_8 + _DAT_00d5c458; but careful with layout.
            // Let's approximate:
            localVec.y = timeUpper + GLOBAL_TIME_OFFSET;
            localVec.z = 0.0f; // not set
            // local_4 was assigned local_4 = *(undefined4 *)(iVar3 + 0x38); which becomes localVec.w

            // Call virtual function on this object at offset 0x58: (1, 0x3f800000, 0)
            uVar4 = (thisPtr->vtable->spawnParticleMethod)(1, 1.0f, 0); // assume returns some handle

            // Call function on the spawn info's vtable at offset 0x170 with localVec and uVar4
            (*(pSpawnInfo->vtable)[0x170/4])(&localVec, uVar4);
        }
    }
}