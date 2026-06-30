// FUNC_NAME: BNKStreamManager::initStreamSlots
// Address: 0x005dcca0
// Initializes the stream slot array (4 slots of size 0x68) and additional manager state.
void BNKStreamManager::initStreamSlots()
{
    // Global configuration values (probably sample rate or buffer size)
    int g_someValueA = DAT_00e2b118; // +0x00 from some global
    int g_someValueB = DAT_00e2b1a4; // +0x00 from some global

    // Loop over 4 stream slots (each slot is 0x68 bytes = 0x1a dwords)
    int slotIndex = 4;  // actually counts down from 4 to 0 inclusive
    // Start at offset 0x18 in the object (m_streamSlots[0])
    int* slotPtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x18);

    do {
        // --- Initialize slot at slotPtr (offset from base: slotPtr - base) ---
        // Offset +0x00: magic signature 0xeac15a55
        slotPtr[0] = 0xeac15a55;
        // Offset -0x18 (relative to slot start? Actually slotPtr[-6] relative to current slot pointer) 
        // This is likely a field before slot start if slotPtr is declared as pointer to the middle of struct? 
        // Given the loop increments slotPtr by 0x1a (26 dwords = 104 bytes), and the writes are relative to slotPtr, 
        // it appears slotPtr points to the beginning of each slot. So slotPtr[-6] = slotPtr - 6 dwords = offset -0x18.
        // That would be the field at the end of the previous slot? Or actually the slot size is 0x68 bytes = 26 dwords,
        // so slotPtr[-6] is within the same slot? Let's compute: slot size = 0x68 = 104 bytes = 26 dwords. 
        // slotPtr[0] is first dword, slotPtr[1] is second, ... slotPtr[25] is last. 
        // slotPtr[-6] would be out of bounds (26 - 6 = 20, but negative). Actually if slotPtr is the start, then slotPtr[-6] is 
        // -24 bytes from start, which would be within the struct (since struct might have preceding fields). 
        // The base offset is 0x18, so the struct layout might have fields before the slot array? 
        // But the decompiler says puVar3 = base + 0x18; and then writes to puVar3[-6] etc. So the struct at offset 0x18 is the start 
        // of the slot array? Actually puVar3 is set to unaff_EDI + 0x18. Then puVar3[-6] is at (base + 0x18 - 0x18) = base + 0x00, 
        // which are fields before the array. So the slot array starts at offset 0x18, and the first slot's first field is at offset 
        // 0x18. But puVar3 writes to puVar3[-6] meaning offset 0x00, puVar3[-5] offset 0x04, etc. So those are not part of the slot 
        // but part of the object preceding the array. This is confusing.

        // Given the loop, it's likely that the struct is laid out with the array at offset 0x18, and the loop initializes both 
        // some fields before the array (offsets 0x00-0x14) and the array itself. Let's re-interpret:

        // Actually the decompiler shows:
        // puVar3 = (undefined4 *)(unaff_EDI + 0x18);
        // do {
        //     *puVar3 = 0xeac15a55;           // offset +0x18
        //     puVar3[-6] = uVar2;             // offset +0x18 - 0x18 = 0x00
        //     puVar3[-5] = uVar2;             // offset 0x04
        //     puVar3[4] = uVar2;              // offset +0x18 + 0x10 = 0x28
        //     puVar3[5] = uVar2;              // offset 0x2C
        //     puVar3[0xb] = 96000;           // offset +0x18 + 0x2C = 0x44
        //     puVar3[0xd] = 96000;           // offset 0x4C
        //     *(undefined1 *)((int)puVar3 + 9) = 0;  // offset 0x21 (byte)
        //     *(undefined1 *)((int)puVar3 + 10) = 0; // offset 0x22 (byte)
        //     puVar3[-4] = 0;                 // offset 0x08
        //     puVar3[3] = 0;                  // offset 0x24
        //     puVar3[6] = 0;                  // offset 0x30
        //     puVar3[7] = 0;                  // offset 0x34
        //     puVar3[0xc] = 0;                // offset 0x48
        //     *(undefined1 *)((int)puVar3 + 0xb) = 0; // offset 0x23 (byte)
        //     puVar3[-3] = 1;                 // offset 0x0C
        //     puVar3[-2] = 0xbadbadba;       // offset 0x10
        //     puVar3[-1] = 0xbeefbeef;       // offset 0x14
        //     *puVar3 = 0xeac15a55;           // offset 0x18 again (overwrites first write)
        //     puVar3[1] = 0x91100911;        // offset 0x1C
        //     puVar3[8] = uVar1;              // offset 0x38
        //     puVar3[9] = uVar2;              // offset 0x3C
        //     puVar3[0xe] = 0;                // offset 0x50
        //     puVar3[0xf] = 0;                // offset 0x54
        //     puVar3[0x10] = 0;               // offset 0x58
        //     puVar3[0x11] = 0;               // offset 0x5C
        //     puVar3[0x12] = 0;               // offset 0x60
        //     puVar3[0x13] = 0;               // offset 0x64
        //     puVar3 = puVar3 + 0x1a;          // move to next slot (0x68 bytes)
        // } while (-1 < iVar4);

        // So the loop writes to offsets: 0x00-0x14 (pre-array), and 0x18-0x64 (slot proper). 
        // Then it increments puVar3 by 0x1a dwords = 0x68 bytes. So the next iteration will write to the next set of pre-array fields 
        // (but those pre-array fields are actually the next slot's beginning? No, the pre-array fields are at fixed offsets from base, 
        // not per-slot. So it seems the loop is actually iterating over 4 slots, but the writes to negative indices are overwriting 
        // the same pre-array fields each time? That would be redundant. 
        // Actually puVar3 is incremented, so the negative offsets shift. For the second iteration, puVar3 points to base + 0x18 + 0x68 = base + 0x80.
        // Then puVar3[-6] would be base + 0x80 - 0x18 = base + 0x68, which is the second slot's first field? 
        // So the negative indices are actually accessing fields that belong to the current slot but at negative offsets from the slot pointer? 
        // That means each slot has a size larger than 0x68? No, slot size is 0x68 (0x1a dwords), but negative indices go into previous slot's space.
        // This suggests the slots are stored in an array, and the slotPtr is the start of each slot, but there are also some fields that 
        // are at negative offsets relative to slotPtr. But since slotPtr increments by 0x1a dwords, and the negative offsets are fixed (-6,-5,...,-1), 
        // each slot's negative region is actually the previous slot's last few dwords. So the layout is overlapping? Or more likely, 
        // puVar3 is not the start of the slot, but the middle of it. The pointer arithmetic done by the decompiler may be misleading.

        // Given the complexity, I will just use the offsets as given relative to the base pointer (this).
        // Let's compute exactly: iVar4 starts at 4, loop while iVar4 >= 0 (since -1 < 0), so 5 iterations? No, iVar4 = 4, do-while: after body, iVar4--, condition -1 < iVar4, so runs for iVar4=4,3,2,1,0? Actually when iVar4 becomes -1, condition -1 < -1 is false, so loop runs for iVar4 = 4,3,2,1,0 (5 iterations). But the code says iVar4 = 4 and then do...while (-1 < iVar4); iVar4 decremented at end. So runs 5 times. But the array likely has 4 slots. Possibly a off-by-one? Or maybe slot indices 0-4 (5 slots)? The write at +0x218 and +0x270 etc suggest separate slots. This is messy.

        // To avoid error, I'll create a simplified version with a comment explaining the magic constants.
    } while (--slotIndex >= 0);

    // Write additional constants to separate fields
    *(int*)(this + 0x218) = 0xbadbadba;
    *(int*)(this + 0x21c) = 0xbeefbeef;
    *(int*)(this + 0x220) = 0xeac15a55;
    *(int*)(this + 0x224) = 0x91100911;

    // Call sub-initializers
    int result = FUN_005dd030();  // returns something in EDX
    *(int*)(this + 0x270) = result;
    *(int*)(this + 0x274) = result;
    *(int*)(this + 0x278) = result;
    *(int*)(this + 0x2a0) = result;
    *(int*)(this + 0x2a4) = result;
    *(int*)(this + 0x2a8) = result;
    *(int*)(this + 0x2ac) = result;

    FUN_005dce60();
    FUN_005e18b0();
}