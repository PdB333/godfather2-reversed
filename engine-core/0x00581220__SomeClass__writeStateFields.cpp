// FUNC_NAME: SomeClass::writeStateFields
void SomeClass::writeStateFields(uint32_t* outBuf) {
    uint32_t* flagsPtr = *(uint32_t**)((uint8_t*)this + 0x68); // pointer to bitfield array (advanced by 8 bytes each call)
    uint32_t flags = *flagsPtr;

    // First group: check flags 0x10, 0x20, 0x200
    if ((flags & 0x10) == 0) {
        if (((flags & 0x20) == 0) || ((int16_t)(*(uint32_t**)((uint8_t*)this + 0x68))[1] < 1)) {
            // No active flag: write sentinel and zeros
            outBuf[3] = DAT_00e2b1a4;
            outBuf[0] = 0;
            outBuf[1] = 0;
            outBuf[2] = 0;
        } else if ((flags & 0x200) == 0) {
            // Write field at +0x1c as a 16-bit pair? (value, value+1)
            FUN_00589450(outBuf, *(int32_t*)((uint8_t*)this + 0x1c), *(int32_t*)((uint8_t*)this + 0x1c) + 1);
        } else {
            // Write field at +0xc
            FUN_00589360(outBuf, *(int32_t*)((uint8_t*)this + 0xC), *(int32_t*)((uint8_t*)this + 0xC) + 1);
        }
    } else {
        // Flag 0x10 set: call handler with field +0x24
        FUN_00589a90(*(int32_t*)((uint8_t*)this + 0x24) + 1);
    }

    // Second group: check flags 0x40, 0x80, 0x100
    flags = **(uint32_t**)((uint8_t*)this + 0x68); // re-read? Or same pointer? Actually it's read again from the same pointer.
    if ((flags & 0x40) == 0) {
        if ((int8_t)(flags & 0xFF) < 0) { // signed check on bit 7 (0x80)
            FUN_00589ef0(*(int32_t*)((uint8_t*)this + 0x44), *(int32_t*)((uint8_t*)this + 0x44) + 1);
        } else if ((flags & 0x100) == 0) {
            FUN_0058a290();
        } else {
            FUN_00589bf0(*(int32_t*)((uint8_t*)this + 0x34), *(int32_t*)((uint8_t*)this + 0x34) + 1);
        }
    } else {
        FUN_0058a1f0();
    }

    // Write the second half of the output buffer (words 4-7)
    // The locals are uninitialized; likely set by the called functions or are from caller's stack.
    // This part may be a fixed header or continuation.
    outBuf[4] = local_c;  // Undefined - likely written by one of the callees (not shown)
    outBuf[5] = local_8;
    outBuf[6] = local_4;
    outBuf[7] = DAT_00e2b1a4;

    // Check bit 0x800 for additional handler
    uint32_t* newFlagsPtr = *(uint32_t**)((uint8_t*)this + 0x68); // same pointer
    if ((*newFlagsPtr & 0x800) != 0) {
        FUN_0058a330(*(int32_t*)((uint8_t*)this + 100), *(int32_t*)((uint8_t*)this + 100) + 1);
    }

    // Advance the flags pointer by 8 bytes (two uint32_ts)
    *(int32_t*)((uint8_t*)this + 0x68) = *(int32_t*)((uint8_t*)this + 0x68) + 8;
}