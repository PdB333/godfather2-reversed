// FUNC_NAME: Entity::updateFrame
void Entity::updateFrame(float deltaTime) {
    // Check flags at byte offset +0x04 (byte flags)
    uint8_t byteFlags = *(uint8_t*)(this + 4);
    if ((byteFlags & 2) == 0) {
        // Sub-update 1 not disabled, call it
        updateSub1(deltaTime); // FUN_005949d0
    }
    if ((byteFlags & 4) == 0) {
        // Sub-update 2 not disabled
        updateSub2(deltaTime); // FUN_00594a30
    }

    // Check flags at int offset +0x7C (int flags)
    uint32_t intFlags = *(uint32_t*)(this + 0x7C);
    if ((intFlags & 0x100) == 0) {
        updateSub3(deltaTime); // FUN_00595230
    }
    if ((intFlags & 0x200) == 0) {
        updateSub4(deltaTime); // FUN_00595300
    }

    // Timer check
    if (((intFlags & 0x400) == 0) && (deltaTime > 0.0f)) {
        uint32_t* timerBase = *(uint32_t**)(this + 0x14C); // +0x14C: pointer to timer array
        if (timerBase != nullptr) {
            float fVar6 = (float)(*(int32_t*)(this + 0x154)) + deltaTime; // +0x154: current timer value (stored as int)
            *(int32_t*)(this + 0x154) = (int32_t)fVar6;
            float* thresholdPtr = (float*)(timerBase + (*(int32_t*)(this + 0x150) * 0x10 - 0x10)); // Array indexing
            if (*thresholdPtr <= fVar6 && fVar6 != *thresholdPtr) {
                *(uint32_t*)(this + 0x7C) |= 0x400; // Set flag on threshold reached
            }
        }
    }

    // More flag checks
    if (*(uint8_t*)(this + 0x7C) & 0x20) {
        updateSub5(1.1754944e-38f); // FUN_00594aa0, very small float
    }
    if (*(uint8_t*)(this + 0x7C) & 0x40) {
        updateSub6(deltaTime); // FUN_00594fb0
    }

    // Process field at +0x14 (stored as uint32_t)
    uint32_t handleField = *(uint32_t*)(this + 0x14); // actually stored as uint32_t, but Ghidra sees as pointer
    float local_74;
    if ((handleField == 0) || ((handleField & 0x20) == 0)) {
        local_74 = (float)((handleField >> 8) & 0xFFFFFF); // Extract high 24 bits
    } else {
        local_74 = (float)(((handleField >> 8) << 8) | 1); // Set bit 0
    }

    // Prepare some stack variables for virtual call
    uint32_t uStack_78 = (*(uint32_t*)(this + 0x10) >> 1) & 0xFFFFFF01;
    float local_7c = deltaTime;
    // Call virtual at vtable+0x68
    (this->vtable[0x68])(); // Virtual update

    // Animation/transition handling
    if ((*(uint8_t*)(this + 0x7C) & 0x10) && (g_globalTimeThreshold < deltaTime)) {
        (this->vtable[0x10])(); // Some virtual
        // Calls to global singleton (DAT_012055a8)
        // Assume g_engineGlobal is a singleton with vtable
        g_engineGlobal->vtable[4](unaff_EDI, unaff_ESI + g_unknownOffset, stackArg);
        g_engineGlobal->vtable[4](stackBuffer, (float)anotherOffset - g_anotherOffset, local_7c, 1.0f, &local_74);
        // Virtual call at vtable+0x38 with multple stack params
        char result = this->vtable[0x38](&uStack_78, &stack_88, stackArr, stackArr2);
        if (result != 0) {
            this->vtable[0x14](); // Additional virtual
        }
    }

    // Clear flag at 0x800
    if (*(uint32_t*)(this + 0x7C) & 0x800) {
        *(uint32_t*)(this + 0x7C) &= ~0x800;
    }

    // Update flag from virtual call at vtable+0x30
    uint32_t retVal = this->vtable[0x30]();
    *(uint32_t*)(this + 0x7C) ^= ((retVal & 0xFF) << 0xB) & 0x800; // Toggle bit 0x800 based on low byte

    return;
}