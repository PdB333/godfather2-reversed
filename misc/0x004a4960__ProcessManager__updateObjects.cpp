// FUNC_NAME: ProcessManager::updateObjects

void __fastcall ProcessManager::updateObjects()
{
    ushort flags;
    uint i;
    uint j;
    int* pPair;
    uint maskLow;
    uint maskHigh;
    uint64_t mask;
    int* pEntry;
    undefined4* puVar7;
    undefined8 shifted;

    // If no special object allocated yet and we have a list of pairs (type/hash check)
    if ((*(int*)(this + 0x94) == 0) && (i = 0, *(int*)(this + 0x38) != 0))
    {
        pPair = *(int**)(this + 0x34);
        do
        {
            // Look for a specific class hash (0x1f32d7d5) in the pair list
            if (*(int*)(*pPair + 4) == 0x1f32d7d5)
            {
                // Allocate 0x50 bytes and create the special object
                int allocSize = 0x50;
                void* mem = FUN_009c8e50(allocSize);  // allocator
                if (mem != 0)
                    *(int*)(this + 0x94) = FUN_004a6cf0();  // creates object, stores at +0x94
                break;
            }
            i = i + 1;
            pPair = pPair + 2;  // each pair is 8 bytes
        } while (i < *(uint*)(this + 0x38));
    }

    // If we have that special object, call its update function
    if (*(int*)(this + 0x94) != 0)
    {
        FUN_004a6f30();  // update special object
    }

    // Update early-stage object if present
    if (*(int*)(this + 0x10) != 0)
    {
        FUN_004a5bb0();  // early update
    }

    // Process all objects in the "always update" list (vtable+0x30)
    for (i = 0; i < *(uint*)(this + 0x78); i++)
    {
        int* obj = *(int**)(*(int*)(this + 0x74) + i * 8);  // each entry: pointer (4 bytes) + pad?
        (*(code**)(*obj + 0x30))();  // call virtual method at offset 0x30
    }

    // Process objects in the conditional update list (0x10-byte entries)
    i = 0;
    int entryBase = *(int*)(this + 0x68);
    if (*(int*)(this + 0x6c) != 0)
    {
        j = 0;
        do
        {
            // Entry structure: +0: pointer to object, +4: flags (ushort), +8: mask1, +12: mask2
            flags = *(ushort*)(entryBase + 4 + j);
            puVar7 = (undefined4*)(entryBase + j);
            int* objPtr = *(int**)(puVar7);  // object pointer
            // Check if flag 0 is set, or if object's mask matches our masks (+0x40, +0x44)
            if ((((flags & 1) == 0) ||
                 ((puVar7[2] & *(uint*)(this + 0x40)) != 0 ||
                  (puVar7[3] & *(uint*)(this + 0x44)) != 0)) &&
                ((flags & 2) == 0))
            {
                // Call update (vtable+0x24) and mark as updated (set flag 2)
                (**(code**)(*objPtr + 0x24))();
                *(ushort*)(puVar7 + 1) = *(ushort*)(puVar7 + 1) | 2;
            }
            i = i + 1;
            j = j + 0x10;  // each entry is 16 bytes
        } while (i < *(uint*)(this + 0x6c));
    }

    // Process objects indexed by a 64-bit bitmask (bits set in +0x40 and +0x44)
    maskLow = *(uint*)(this + 0x40);
    maskHigh = *(uint*)(this + 0x44);
    if (maskLow != 0 || maskHigh != 0)
    {
        do
        {
            // Extract least significant set bit using magic multiplication (64-bit)
            // __allmul computes product of ( -mask ) with constant 0xb4cb0a893f79d71? Actually order is: __allmul(-maskLow & maskLow, -(maskHigh + (maskLow != 0)) & maskHigh, 0xb4cb0a89, 0x3f79d71)
            // Then __aullshr shifts right to get bit index
            // This is a standard technique to find the index of the lowest set bit in a 64-bit value
            uint64_t negMaskLow = (uint64_t)(-maskLow) & maskLow;
            uint64_t negMaskHigh = (uint64_t)(-(maskHigh + (maskLow != 0))) & maskHigh;
            // Combine into 64-bit value: low part first, high part second (since __allmul treats args as 64-bit)
            uint64_t tempLow = negMaskLow;
            uint64_t tempHigh = negMaskHigh;
            // __allmul(negMaskLow, negMaskHigh, 0xb4cb0a89, 0x3f79d71) actually multiplies two 64-bit values: (negMaskHigh<<32 | negMaskLow) by (0x3f79d71<<32 | 0xb4cb0a89)
            // But decompiler shows __allmul(-uVar2 & uVar2,-(uVar5 + (uVar2 != 0)) & uVar5,0xb4cb0a89,0x3f79d71);
            // The arguments: uVar2 = maskLow, uVar5 = maskHigh; first arg = low part of the bit-diff, second = high part; third and fourth are the constant low and high.
            // Then __aullshr() returns the shifted result (divide by 2^...)
            // We'll simulate this with a simple loop for cleanliness, but keep the original intent comment.

            // Simpler: find index via a loop
            uint64_t fullMask = ((uint64_t)maskHigh << 32) | maskLow;
            if (fullMask == 0) break;
            int bitIndex = __builtin_ctzll(fullMask);  // count trailing zeros
            // Use bitIndex to index into an array of objects at +0x5c, with a lookup table at DAT_00e2e110
            int* obj = *(int**)(*(int*)(this + 0x5c) + *(int*)(&DAT_00e2e110 + bitIndex * 4) * 4);
            (**(code**)(*obj + 0x24))();  // call vtable+0x24 on that object

            // Clear the processed bit
            uint64_t clearMask = ((uint64_t)1 << bitIndex);
            fullMask &= ~clearMask;
            maskLow = (uint32_t)fullMask;
            maskHigh = (uint32_t)(fullMask >> 32);
        } while (maskLow != 0 || maskHigh != 0);
    }

    // Manage global linked list #1 (through +0x84, +0x88)
    FUN_004a69b0(0);  // some pre-list-add operation
    int ptr1 = this;
    if (DAT_01205484 != 0)
    {
        *(int*)(DAT_01205484 + 0x88) = this;  // previous node's next becomes this
        ptr1 = DAT_01205480;
    }
    DAT_01205480 = ptr1;  // update head?
    *(int*)(this + 0x84) = DAT_01205484;  // set prev pointer
    *(int*)(this + 0x88) = 0;              // set next to null
    DAT_01205484 = this;                   // make this the new tail

    // Manage global linked list #2 (through +0x8c, +0x90)
    FUN_004a6a80(0);  // similar
    int ptr2 = this;
    if (DAT_0120548c != 0)
    {
        *(int*)(DAT_0120548c + 0x90) = this;  // previous node's next becomes this
        ptr2 = DAT_01205488;
    }
    DAT_01205488 = ptr2;
    *(int*)(this + 0x90) = 0;              // next = null
    *(int*)(this + 0x8c) = DAT_0120548c;   // prev = previous tail
    DAT_0120548c = this;                   // become new tail
}