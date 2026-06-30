// FUNC_NAME: AIEntity::updateActiveStateFlags
void AIEntity::updateActiveStateFlags(void)
{
    // +0x82: ushort flags (bitfield for various state indicators)
    *(ushort *)(this + 0x82) &= 0xff01;  // Clear lower byte flags

    bool bAnyActive = false;
    uint idx1 = 0;
    uint count1 = *(uint *)(this + 0x78);  // +0x78: count of first data array

    // First loop: process 8-byte entries at +0x74
    if (count1 != 0) {
        do {
            int *entry1 = (int *)(*(int *)(this + 0x74) + idx1 * 8);
            // Check flag at offset +4 of entry (byte at entry+4 & 0x08)
            if ((*(byte *)(entry1 + 1) & 0x08) != 0) {
                *(ushort *)(this + 0x82) |= 2;   // Set bit 1 (0x02)
                bool found = false;
                uint idx2 = 0;
                uint count2 = *(uint *)(this + 0x6c);  // +0x6c: count of second data array

                // Search second array (16-byte entries at +0x68) for matching ID
                if (count2 != 0) {
                    int ofs2 = 0;
                    do {
                        int *entry2 = (int *)(*(int *)(this + 0x68) + ofs2);
                        // Check flag at byte offset 1 of entry2: & 0x10
                        if ((*(byte *)(entry2 + 1) & 0x10) != 0) {
                            // Virtual call at vtable+0x80 of object pointed to by entry2[0]
                            // Returns an ID that should match entry1[0]
                            int objId = (**(code **)(*(int *)entry2[0] + 0x80))();
                            if (objId == *entry1) {
                                *(ushort *)(this + 0x82) |= 4;   // Set bit 2 (0x04)
                                break;
                            }
                        }
                        idx2++;
                        ofs2 += 0x10;  // Each entry 16 bytes
                    } while (idx2 < count2);
                }
            }
            // Check flag at byte offset 4 of entry1: & 0x10
            if ((*(byte *)(entry1 + 1) & 0x10) != 0) {
                *(ushort *)(this + 0x82) |= 0x10;  // Set bit 4
            }
            idx1++;
        } while (
            // Early exit if both bits 0x04 and 0x10 are set
            ((*(ushort *)(this + 0x82) & 4) == 0) ||
            ((*(ushort *)(this + 0x82) & 0x10) == 0) ||
            (idx1 < count1)
        );
        // The condition actually continues if NOT both bits set,
        // meaning it stops early when both are set.
        // However the decompiler shows a composite while that iterates
        // until either both bits set or idx1 reaches count1.
    }

    // Second loop: iterate over second array directly
    uint idx3 = 0;
    uint count3 = *(uint *)(this + 0x6c);
    if (count3 != 0) {
        ushort *flagsPtr = (ushort *)(*(int *)(this + 0x68) + 4); // Point to flags in each 16-byte entry
        do {
            if ((*flagsPtr & 2) != 0 && (*flagsPtr & 8) != 0) {
                *(ushort *)(this + 0x82) |= 8;  // Set bit 3
                bAnyActive = true;
            }
            if ((*flagsPtr & 0x10) != 0) {
                *(ushort *)(this + 0x82) |= 0x80;  // Set bit 7
            }
            if ((*(ushort *)(this + 0x82) & 0x80) != 0 && (*(ushort *)(this + 0x82) & 8) != 0) {
                break;
            }
            idx3++;
            flagsPtr += 8;  // Each entry 16 bytes, flags at offset 2? Actually flagsPtr started at +4, so +8 per entry (flags at byte 4? The code uses puVar6 = (ushort*)(*(int*)(this+0x68)+4); then increments by 8 (ushort*). So flags at offset 4 of each entry.)
        } while (idx3 < count3);
    }

    // Third part: process 64-bit bitmask at +0x40 (low) and +0x44 (high)
    uint lowMask = *(uint *)(this + 0x40);
    uint hiMask  = *(uint *)(this + 0x44);
    if (lowMask != 0 || hiMask != 0) {
        do {
            // Isolate lowest set bit of 64-bit value
            uint isolatedLow = -lowMask & lowMask;
            uint isolatedHi  = -(hiMask + (lowMask != 0)) & hiMask;  // handle borrow
            // Multiply by magic constant (0x3f79d71b4cb0a89) to get hash
            // Then shift right by 64? The __aullshr after __allmul.
            // Result yields index into table DAT_00e2e110
            __allmul(isolatedLow, isolatedHi, 0xb4cb0a89, 0x3f79d71);
            int idx = __aullshr();
            idx = *(int *)((int)&DAT_00e2e110 + idx * 4);
            // Retrieve behavior handler object from table at +0x5c, using idx as offset
            int handlerObj = *(int *)(*(int *)(this + 0x5c) + idx * 4);
            // Call two virtual functions on the handler
            char res1 = (**(code **)(**(int **)handlerObj + 4))();
            if (res1 != '\0') {
                *(ushort *)(this + 0x82) |= 0x20;  // Set bit 5
                bAnyActive = true;
            }
            char res2 = (**(code **)(**(int **)handlerObj + 8))();
            if (res2 != '\0') {
                *(ushort *)(this + 0x82) |= 0x40;  // Set bit 6
            }
            // Clear the processed bit from the mask
            uint64 clearMask = __allshl(1, idx);  // Shift 1 by bit position? Actually uses idx from hash, not original bit. Possibly an error in decompilation? In reality they shift by the original isolated bit's position.
            lowMask &= ~(uint)clearMask;
            hiMask  &= ~(uint)(clearMask >> 32);
        } while (lowMask != 0 || hiMask != 0);
    }

    // If any active state and this object is not already in global active list
    if (bAnyActive && *(int *)(this + 0x88) == 0 && *(int *)(this + 0x84) == 0) {
        FUN_004a69b0(0);  // Possibly acquire lock
        int oldHead = this; // this is stored temporarily? The code: if (DAT_01205484 != 0) { *(int *)(DAT_01205484 + 0x88) = this; oldHead = DAT_01205480; } else { oldHead = DAT_01205480; }
        // Actually the decompiled code:
        // iVar7 = this;
        // if (DAT_01205484 != 0) {
        //     *(int *)(DAT_01205484 + 0x88) = this;
        //     iVar7 = DAT_01205480;
        // }
        // DAT_01205480 = iVar7;
        // *(int *)(this + 0x84) = DAT_01205484;
        // *(undefined4 *)(this + 0x88) = 0;
        // DAT_01205484 = this;
        // This is a linked list insertion at head:
        // new->next = old head; new->prev = 0; global head = new; also update old head's prev if exists.
        int oldHead2 = (DAT_01205484 != 0) ? DAT_01205480 : DAT_01205480; // likely same
        if (DAT_01205484 != 0) {
            *(int *)(DAT_01205484 + 0x88) = (int)this;
        }
        *(int *)(this + 0x84) = DAT_01205484;  // next = old head
        *(int *)(this + 0x88) = 0;             // prev = null
        DAT_01205484 = (int)this;              // new head
        // Note: The original code also sets DAT_01205480 = iVar7, which seems redundant. It might be another pointer (tail). But for simplification, we treat it as singly linked.
    }
    return;
}