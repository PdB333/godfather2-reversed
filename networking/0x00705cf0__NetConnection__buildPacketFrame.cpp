// FUNC_NAME: NetConnection::buildPacketFrame
void __thiscall NetConnection::buildPacketFrame(void* unusedParam, int* outBuffer)
{
    // +0x118: char slotActive[35]; // per-slot active flags
    // +0xf4: bool flag0xf4; // affects bit 31 of high mask
    // +0x18: struct GhostSlot slots[11]; // each 0x14 bytes, see GhostSlot layout

    // ---- Build 64-bit slot mask ----
    uint lowMask = 0;
    uint highMask = 0;
    for (int i = 0; i < 35; i++) {
        if (this->slotActive[i] != '\0') {
            if (i < 32) {
                lowMask |= (1 << i);
            } else {
                highMask |= (1 << (i - 32));
            }
        }
    }

    // Set/clear bit 31 of highMask based on byte at +0xf4
    if (this->flag0xf4 == 1) {
        highMask |= 0x80000000;
    } else {
        highMask &= 0x7FFFFFFF;
    }

    // Write 64-bit mask to output buffer
    outBuffer[0] = lowMask;
    outBuffer[1] = highMask;

    // ---- Serialize each of the 11 ghost slots ----
    uint* outputPtr = (uint*)(outBuffer + 2); // points to slot data
    for (int slotIdx = 0; slotIdx < 11; slotIdx++) {
        GhostSlot* slot = &this->slots[slotIdx];
        void* obj = slot->pObject;   // +0x00 of slot
        uint count = slot->count;    // +0x08
        uint maxCount = slot->maxCount; // +0x0c

        // Determine flags word for this slot
        uint flags = 0;
        if (!(maxCount < count) && !(count != 0 && (obj == nullptr || obj == (void*)0x48))) {
            flags = count;
        }

        *outputPtr = flags;
        uint* dataPtr = outputPtr + 1;

        // If slot is active and object is valid (not null, not 0x48)
        if (flags != 0 && obj != nullptr && obj != (void*)0x48) {
            // Copy 8 fields from object: offsets +0x264, +0x268, +0x26c, +0x270
            // and offsets -0x28, -0x24, -0x20, -0x1c (relative to obj pointer)
            dataPtr[0] = *(uint*)((char*)obj + 0x264);
            dataPtr[1] = *(uint*)((char*)obj + 0x268);
            dataPtr[2] = *(uint*)((char*)obj + 0x26c);
            dataPtr[3] = *(uint*)((char*)obj + 0x270);
            dataPtr[4] = *(uint*)((char*)obj - 0x28);
            dataPtr[5] = *(uint*)((char*)obj - 0x24);
            dataPtr[6] = *(uint*)((char*)obj - 0x20);
            dataPtr[7] = *(uint*)((char*)obj - 0x1c);
            dataPtr += 8;

            // For first 5 slots, write extra data
            if (slotIdx < 5) {
                // Clamp field at obj+0x4c8 to max 4
                uint clamped = (uint)(4 < *(uint*)((char*)obj + 0x4c8));
                clamped = ~-clamped & *(uint*)((char*)obj + 0x4c8); // if original <=4, value; else 0
                *dataPtr++ = clamped;

                // Call helper to get a sequence number or CRC
                *dataPtr++ = FUN_007013c0();
            }
            outputPtr = dataPtr;
        } else {
            outputPtr = dataPtr; // advance past flags only
        }
    }

    // ---- Write optional extra data block ----
    // +0x144: bool hasExtraData
    // +0x13c: uint extraDataSize
    // +0x140: byte* pExtraData
    if (this->hasExtraData != 0) {
        *outputPtr = this->extraDataSize;
        outputPtr++;
        if (this->extraDataSize != 0) {
            byte* src = this->pExtraData;
            for (uint i = 0; i < this->extraDataSize; i++) {
                *(byte*)outputPtr = src[i];
                outputPtr = (uint*)((byte*)outputPtr + 1);
            }
        }
    }

    // ---- Write sentinel ----
    *outputPtr = 0xABBA;
}

// Helper stub for the callee at 0x007013c0
uint __cdecl FUN_007013c0(void); // defined elsewhere