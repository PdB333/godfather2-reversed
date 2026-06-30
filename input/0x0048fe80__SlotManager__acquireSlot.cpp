// FUNC_NAME: SlotManager::acquireSlot
// Address: 0x0048fe80
// Reconstructed C++ for The Godfather 2 (EA EARS engine)
// This function attempts to acquire a slot in a global array of 0x38-byte structures,
// then registers a callback pair (0x48fd20, 0x48fd50) into a 12-byte callback list.

void __fastcall SlotManager::acquireSlot(int* this, int arg2) // __fastcall with this in ecx, arg2 in edx
{
    int iVar1;
    SlotStruct* puVar2; // pointer to a slot entry (0x38 bytes)
    byte* pbVar3;
    uint uVar5;
    bool bVar4;

    // Virtual call: likely a debug/log method (vtable[3])
    // Signature unknown, but passes a string pointer and a data pointer
    ((void (*)(SlotManager*, void*, int, int, int, void*))(*(void***)this)[3])(
        this,
        PTR_PTR_010f0bb4, // some string or object
        0, 0, 0,
        &PTR_DAT_0110a2dc
    );

    bVar4 = g_SomeFlag != 0; // DAT_012053da

    // Call internal helper (maybe initialisation)
    FUN_0048fe20(this);

    iVar1 = g_MaxDimension; // DAT_0110ae28

    uVar5 = this[0x29]; // current slot index at offset 0xA4

    // Bounds check for the slot array (max 0x1000 entries)
    if (uVar5 < 0x1000) {
        puVar2 = (SlotStruct*)(g_SlotArray + uVar5 * sizeof(SlotStruct)); // sizeof(SlotStruct) = 0x38
    } else {
        puVar2 = nullptr;
    }

    // Check if the product of two unsigned shorts in the slot (width * height) is below a threshold
    if ((int)((uint)puVar2->width * (uint)puVar2->height) < iVar1 * iVar1) {
        // Failed: mark as invalid
        uVar5 = (uint)-1;
    } else {
        // Validate current index pointer
        if ((uVar5 > 0xfff) || (uVar5 * sizeof(SlotStruct) == -0x11a0f28)) {
            iVar1 = -1;
            goto done_assign;
        }
        // Get a random index
        uVar5 = FUN_00606b50();
        // Validate random index
        if ((uVar5 > 0xfff) || (&g_SlotArray[uVar5] == nullptr)) {
            iVar1 = -1;
            goto done_assign;
        }
        // Check if the slot is free (status byte at offset 0 must be <= 1)
        if (g_SlotArray[uVar5].status > 1) {
            iVar1 = -1;
            goto done_assign;
        }
    }

    // Allocate or create something related to the slot
    // Arguments: flags, size (0x210098), iVar1, iVar1, 1, uVar5
    iVar1 = FUN_00606c80(
        (-bVar4 & 0x11U) + 3,   // flags: 3 if bVar4=0, 20 if bVar4=1
        0x210098,               // constant size
        iVar1,                  // duplicate of iVar1 (maybe previous index)
        iVar1,                  // again
        1,                      // count
        uVar5                   // slot index to use
    );

done_assign:
    this[0x2a] = iVar1; // store result at offset 0xA8

    // Validate existing callback entries (each 12 bytes)
    uVar5 = 0;
    if (g_CallbackCount != 0) {
        pbVar3 = (byte*)g_CallbackArray; // array base
        do {
            if (0x80 < *pbVar3) { // first byte of callback entry should be <= 0x80
                FUN_00609bf0(); // error handler
                return;
            }
            uVar5++;
            pbVar3 += sizeof(CallbackEntry); // 0x0c
        } while (uVar5 < g_CallbackCount);
    }

    // Append a new callback entry if space exists (max 0x20 entries)
    if (g_CallbackCount < 0x20) {
        int index = g_CallbackCount;
        // Write a 64-bit value: two function pointers (0x48fd20 and 0x48fd50)
        *(uint64*)(&g_CallbackArray[index]) = 0x48fd500048fd20ULL;
        // Write status word: arg2's high bits (shifted) OR'd with 0x80
        *(uint*)((byte*)&g_CallbackArray[index] + 8) = CONCAT31((int3)((uint)arg2 >> 8), 0x80);
        g_CallbackCount++;
    }
}

// Structure definitions (as comments, not part of output):
// SlotStruct (size 0x38):
//   +0x00 : uint8 status
//   +0x02 : uint16 width
//   +0x04 : uint16 height
//   ... (rest unknown)

// CallbackEntry (size 0x0c):
//   +0x00 : uint32 func1 (lower of 8-byte value)
//   +0x04 : uint32 func2 (upper)
//   +0x08 : uint32 status

// Global variables:
// g_SomeFlag = DAT_012053da
// g_MaxDimension = DAT_0110ae28
// g_SlotArray = DAT_011a0f28 (array of SlotStruct)
// g_CallbackCount = DAT_012224a8
// g_CallbackArray = DAT_01222328 (array of CallbackEntry, but note that in the code, the first entry's data starts at &g_CallbackArray[0] and the status is at offset 8)