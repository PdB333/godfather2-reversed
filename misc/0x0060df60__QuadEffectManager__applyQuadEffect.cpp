// FUNC_NAME: QuadEffectManager::applyQuadEffect
void __fastcall QuadEffectManager::applyQuadEffect(uint param1, uint param2, uint sourceTextureIndex, uint destTextureIndex) {
    uint savedParam2 = g_savedEffectParam2; // DAT_011f38f4
    uint savedParam1 = g_savedEffectParam4; // DAT_011f38f0

    // Validate indices and check flags (bit 3 = 8) in ScreenEffectEntry +0xc
    ScreenEffectEntry* srcEntry = (sourceTextureIndex < 0x1000) ? &g_screenEffectEntries[sourceTextureIndex] : nullptr;
    if ((srcEntry != nullptr) && ((srcEntry->flags & 8) != 0)) {
        ScreenEffectEntry* dstEntry = (destTextureIndex < 0x1000) ? &g_screenEffectEntries[destTextureIndex] : nullptr;
        if ((dstEntry == nullptr) || ((dstEntry->flags & 8) == 0)) {
            FUN_00618b80(); // Probably error/cleanup
            return;
        }
    }

    // Save current effect transform (4x4 matrix?) at offset based on g_currentEffectIndex * 0x18
    float savedMatrix[4];
    int indexOffset = g_currentEffectIndex * 0x18;
    savedMatrix[0] = *(float*)(&g_currentEffectMatrixBase + indexOffset); // DAT_011f3918
    savedMatrix[1] = *(float*)(&g_currentEffectMatrixBase + indexOffset + 4);
    savedMatrix[2] = *(float*)(&g_currentEffectMatrixBase + indexOffset + 8);
    savedMatrix[3] = *(float*)(&g_currentEffectMatrixBase + indexOffset + 12);

    // Set new effect targets
    g_savedEffectParam4 = destTextureIndex;
    g_savedEffectParam2 = param2;

    // Call helper functions to set up effect (clear, scale, enable)
    FUN_00609340(0, savedParam1, savedParam2); // restore? or set?
    FUN_0060db60(0, 0, 0, 1.0f, 1.0f); // probably setScale(1,1)
    FUN_00609810(1); // enable rendering?

    // Find the effect object by class name "SM_QuadEffectClass"
    int classId = FUN_0060d740("SM_QuadEffectClass");
    EffectObject* effectObj = nullptr;
    for (EffectObject* node = g_effectClassListHead; node != nullptr; node = node->next) {
        if (classId == node->classId) {
            effectObj = node;
            break;
        }
    }

    // Set various effect quality parameters (clamping between min/max)
    // These are likely brightness, contrast, color balance etc.
    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0x19, 0x19);
    g_effectFlags1 = 5; // _DAT_011f3a3c

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0x18, 0x18);
    g_effectFlags2 = 0;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0xf, 0xf);
    g_effectFlags3 = 0;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0x1b, 0x1b);
    g_effectFlags4 = 1;

    FUN_00417cf0(1, 2, 1); // set some mode (e.g., alpha blend)

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 7, 7);
    g_effectLevel1 = 0;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0xe, 0xe);
    g_effectLevel2 = 0;

    clampEffectQualitySetting(&g_anotherMinQuality, &g_anotherMaxQuality, 0xa8, 0xa8);
    g_effectGamma = 0xf;

    clampEffectQualitySetting(&g_anotherMinQuality, &g_anotherMaxQuality, 0xbe, 0xbe);
    g_effectContrast = 0xf;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0x16, 0x16);
    g_effectLevel3 = 1;

    // Modify effect object properties
    effectObj->field_0x4e = 6; // offset 0x13c? (4*0x4e)
    effectObj->field_0x5 = effectObj->field_0x56; // copy some field
    effectObj->field_0x4 = effectObj->field_0x6a; // another copy

    if (g_currentEffectPointer == effectObj) {
        FUN_0060a460(effectObj->field_0x56); // specialize?
    }

    FUN_00611500(); // Finalize effect?

    // If source texture index is valid and entry state is < 4, modify its flags
    if ((sourceTextureIndex != 0xFFFFFFFF) && (sourceTextureIndex < 0x1000)) {
        int offset = sourceTextureIndex * 0x38;
        byte* entryBase = (byte*)&g_screenEffectEntries[sourceTextureIndex];
        if (entryBase != nullptr && entryBase[0] < 4) {
            if (*(int*)(entryBase + 0x14) != 0) { // +0x14 = some resource handle?
                FUN_00606e60(*(int*)(entryBase + 0x14), 0x3214000); // load resource?
            }
            // Set flags: bit 21, 18? (0x210000 = 0x00210000) and clear bits 23,22? (0xffadffff)
            *(uint*)(entryBase + 0x0c) = (*(uint*)(entryBase + 0x0c) & 0xffadffff) | 0x210000;
            FUN_006189c0(); // post-process?
        }
    }

    effectObj->sourceTexture = sourceTextureIndex; // offset 0x100 (0x40*4)

    if ((g_currentEffectPointer == effectObj) && (effectObj->field_0x3f != 0)) {
        FUN_006063b0(); // special handling
    }

    // Call virtual functions
    (*(effectObj->vtable + 0x18))(); // prepare/render?
    // Allocate some control points/quads
    float* controlData = (float*)FUN_0060cd00(0xd, 4, 0, 1, 0); // size: 0xd*4=52? Actually 13 floats
    if (controlData != nullptr) {
        controlData[0] = g_constant1; // DAT_00e2eff4
        controlData[1] = g_constant2; // DAT_00e2b1a4
        controlData[2] = 0.0f;
        controlData[3] = 0.0f;
        controlData[4] = g_constant2;
        controlData[5] = g_constant2;
        controlData[6] = g_constant2;
        controlData[7] = 0.0f;
        controlData[8] = g_constant2;
        controlData[9] = g_constant1;
        controlData[10] = g_constant2;
        controlData[11] = g_constant2;
        controlData[12] = g_constant1;
        controlData[13] = g_constant1;
        controlData[14] = 0.0f;
        controlData[15] = g_constant2;
        FUN_0060cde0(); // commit allocation?
    }

    // Second virtual call
    (*(effectObj->vtable + 0x20))(); // finalize/render?

    // Process dest texture entry
    ScreenEffectEntry* destEntry = (destTextureIndex < 0x1000) ? &g_screenEffectEntries[destTextureIndex] : nullptr;
    FUN_00606830(destTextureIndex, destEntry);

    // Set effect parameters back to a different mode (transition?)
    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0x19, 0x19);
    g_effectFlags1 = 7;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0x18, 0x18);
    g_effectFlags2 = 0;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0xf, 0xf);
    g_effectFlags3 = 0;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 7, 7);
    g_effectLevel1 = 1;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0xe, 0xe);
    g_effectLevel2 = 1;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0x1b, 0x1b);
    g_effectFlags4 = 0;

    FUN_00417cf0(1, 5, 6); // another mode

    uint restoreParam2 = g_savedEffectParam2;
    uint restoreParam1 = g_savedEffectParam4;

    clampEffectQualitySetting(&g_minEffectQuality, &g_maxEffectQuality, 0x16, 0x16);
    g_effectLevel3 = 1;

    // Restore previous effect state
    g_savedEffectParam4 = savedParam1;
    g_savedEffectParam2 = savedParam2;
    FUN_00609340(0, restoreParam1, restoreParam2); // restore original?

    // Restore the saved matrix
    float constant2 = g_constant2; // DAT_00e2b1a4
    indexOffset = g_currentEffectIndex * 0x18;
    *(float*)(&g_currentEffectMatrixBase + indexOffset) = savedMatrix[0];
    *(float*)(&g_currentEffectMatrixBase + indexOffset + 4) = savedMatrix[1];
    *(float*)(&g_currentEffectMatrixBase + indexOffset + 8) = savedMatrix[2];
    *(float*)(&g_currentEffectMatrixBase + indexOffset + 12) = savedMatrix[3];
    *(float*)(&g_currentEffectMatrixBase + indexOffset + 16) = 0.0f; // AT
    *(float*)(&g_currentEffectMatrixBase + indexOffset + 20) = constant2;

    FUN_00609500(savedMatrix[3], 1.0f); // finalize transformation?
    return;
}