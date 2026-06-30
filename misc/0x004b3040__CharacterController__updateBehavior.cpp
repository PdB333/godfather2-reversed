// FUNC_NAME: CharacterController::updateBehavior
int CharacterController::updateBehavior(int* this) {
    // this points to a structure with a self-referential pointer at offset 0
    void* base = (void*)*this; // self pointer
    uint8_t index = *(uint8_t*)(this + 1); // second int treated as byte, so offset 4
    uint32_t count = *(uint32_t*)((int)base + 0x6f8);

    float* pfVar4;
    if (index < count) {
        pfVar4 = (float*)((int)base + 0x138 + index * 0x5c);
    } else {
        pfVar4 = nullptr;
    }

    // If some threshold is met, use default fallback data
    if (*(float*)((int)base + 0xc4) <= g_fZero) { // DAT_00e44598 likely 0.0
        pfVar4 = &local_70;
        // Initialize local data (rotation/scale? )
        local_50 = 0;
        local_4c = 0;
        local_48 = 0;
        local_44 = 0;
        local_3c = 0;
        local_38 = 0;
        local_34 = 0;
        local_30 = 0;
        local_28 = 0;
        local_24 = 0;
        local_20 = 0;
        local_1c = 0;
        local_58 = 0;
        local_54 = g_fOne; // DAT_00e2b1a4 likely 1.0
        local_40 = g_fOne;
        local_2c = g_fOne;
        local_18 = g_fOne;
        local_68 = g_fZero;
        local_6c = g_fZero;
        local_70 = g_fZero;
        local_5c = g_fZero; // DAT_00e44778 likely 0.0
        local_60 = g_fZero;
        local_64 = g_fZero;
    }

    // Process audio/animation data
    FUN_0061ecd0(pfVar4);
    FUN_0061f0d0();

    // Get some time/speed value
    float fVar6;
    int iVar2;
    if (*(int*)((int)base + 0x98) == 0) {
        fVar6 = 0.0f;
        iVar2 = -1;
    } else {
        fVar6 = *(float*)(*(int*)((int)base + 0x98) + 0x1c8);
        iVar2 = FUN_00d01890(); // likely returns game time or frame count
    }

    float fVar1 = (float)iVar2;
    if (iVar2 < 0) {
        fVar1 += g_fHalf; // DAT_00e44578 likely 0.5
    }
    int value = (int)((fVar1 / fVar6) * g_fSomeScale); // DAT_00e2e230 scale factor

    // If the index byte is zero, notify attached objects
    if (*(char*)(this + 1) == '\0') {
        int* attachmentList = (int*)((int)base + 0xb4);
        // Note: The decompiler suggests a single iteration;
        // likely a linked list where *attachmentList is head pointer
        if (*attachmentList != 0) {
            do {
                (**(code**)(**attachmentList + 4))(value);
                attachmentList = (int*)((int)base + 0xb4);
                // The loop condition is unclear; assuming it processes each list node
            } while (0); // placeholder – actual assembly may differ
        }
    }

    FUN_009c8eb0(this);
    return 1;
}