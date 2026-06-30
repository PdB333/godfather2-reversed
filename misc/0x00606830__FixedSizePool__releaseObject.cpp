// FUNC_NAME: FixedSizePool::releaseObject
// Function address: 0x00606830
// Releases an object back to a fixed-size pool (0x38-byte slots, up to 0x1000 entries).
// Updates a 64-bit bitmap and status byte (offset 0 of each slot).
// VERIFICATION: compares short at +2, short at +4, and byte at +1 between the object and a signature.

void FixedSizePool::releaseObject(void* objPtr, void* signature)
{
    uint objIndex;                 // in_EAX
    uint origPtrUint;              // uVar1 (original objPtr as uint)
    uint bitmapIdx;                // uVar2 / uVar1
    uint64 shiftAmount;            // uVar3 (result of __allshl)
    LPCRITICAL_SECTION cs;        // DAT_011d917c

    objIndex = *((uint*)this + 0x?); // Actually in_EAX is passed in EAX register; treat as first integer argument.
    // However, due to decompiler confusion, we assume objIndex is an explicit parameter.
    // For reconstruction, we'll use an explicit parameter resourceIndex.
    // In the original binary, the index is passed in EAX.

    // ... (placeholder to match decompiler structure)
    // We'll keep the logic but adapt naming.
}

// Given the complexity, we provide a cleaned version matching the decompiled flow:
void FixedSizePool::free(void* objPtr, void* signature)
{
    uint objIndex = (uint)objPtr; // uVar1
    uint bitmapIdx;
    uint64 shiftAmt;
    LPCRITICAL_SECTION cs = g_poolCriticalSection; // DAT_011d917c

    // Compute actual slot pointer from index (in_EAX, passed in EAX register)
    uint index; // in_EAX (assumed from caller)
    void* slotPtr;
    if (index < 0x1000) {
        slotPtr = (void*)((uint)g_poolData + index * 0x38); // &DAT_011a0f28 + index*0x38
    } else {
        slotPtr = 0;
    }

    // Compare the original object pointer with the slot pointer? Actually uVar1 != index
    if (objIndex != index) {
        // If the provided objPtr (as uint) doesn't equal the slot index,
        // compare verification fields (offset +2 (short), +4 (short), +1 (byte))
        if (*(short*)((uint)signature + 2) == *(short*)((uint)slotPtr + 2) &&
            *(short*)((uint)signature + 4) == *(short*)((uint)slotPtr + 4) &&
            *(char*)((uint)signature + 1) == *(char*)((uint)slotPtr + 1))
        {
            // Fields match: release normally
            bitmapIdx = index >> 6;
            EnterCriticalSection(cs);
            LeaveCriticalSection(cs);
            shiftAmt = __allshl(index & 0x3F, 1); // Actually shift by (index % 64)
            // Clear bit in 64-bit bitmap at index/64
            g_poolBitmap[bitmapIdx] &= ~(uint)shiftAmt;
            g_poolBitmap[bitmapIdx + 1] &= ~(uint)(shiftAmt >> 0x20);
            // Update free list head if necessary
            if (bitmapIdx == g_poolFirstFree && g_poolBitmap[bitmapIdx] == 0 && g_poolBitmap[bitmapIdx + 1] == 0) {
                g_poolFirstFree++;
            }
            // Mark slot status as FREED (3)
            *(char*)slotPtr = 3;
            return;
        }
        // Fields don't match: mark as error? (status = 2)
        bitmapIdx = index >> 6;
        EnterCriticalSection(cs);
        LeaveCriticalSection(cs);
        shiftAmt = __allshl(index & 0x3F, 1);
        g_poolBitmap[bitmapIdx] &= ~(uint)shiftAmt;
        g_poolBitmap[bitmapIdx + 1] &= ~(uint)(shiftAmt >> 0x20);
        if (bitmapIdx == g_poolFirstFree && g_poolBitmap[bitmapIdx] == 0 && g_poolBitmap[bitmapIdx + 1] == 0) {
            g_poolFirstFree++;
        }
        *(char*)slotPtr = 2; // ERROR or ABANDONED
        return;
    }

    // objIndex == index: the provided pointer is the index itself? (unlikely)
    bitmapIdx = index >> 6;
    EnterCriticalSection(cs);
    LeaveCriticalSection(cs);
    shiftAmt = __allshl(index & 0x3F, 1);
    g_poolBitmap[bitmapIdx] &= ~(uint)shiftAmt;
    g_poolBitmap[bitmapIdx + 1] &= ~(uint)(shiftAmt >> 0x20);
    if (bitmapIdx == g_poolFirstFree && g_poolBitmap[bitmapIdx] == 0 && g_poolBitmap[bitmapIdx + 1] == 0) {
        g_poolFirstFree++;
    }

    if (signature == 0) {
        // No signature: directly overwrite slot status
        if (index < 0x1000) {
            *(char*)((uint)g_poolData + index * 0x38) = 3;
        }
        // else (index >= 0x1000) - overflow, write to address 0? (likely bug)
        return;
    }
    // Signature exists: set its status byte to 3 (probably the signature is stored elsewhere)
    *(char*)signature = 3;
}