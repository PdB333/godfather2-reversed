// FUNC_NAME: StoreManager::buildSortedItemList
// Function address: 0x00984630
// Reconstructed from Ghidra decompilation of The Godfather 2 (2008, EA EARS engine)
// This function builds a sorted list of items from a global store collection, used for UI display.

#include <cstdlib> // for qsort

// Forward declarations of called functions (inferred from context)
extern int __fastcall FUN_0089c630(); // Returns some state byte
extern void __fastcall FUN_009842e0(); // Resets iterator or list
extern void* __fastcall FUN_00984440(); // Allocates or retrieves a slot for an item entry
extern short __fastcall FUN_008a6320(int param); // Converts item ID to short (maybe price or quantity)
extern int __fastcall FUN_004bb600(void* obj); // Gets some property from an object
extern void __fastcall FUN_004d3e20(int value); // Sets a value (maybe UI related)
extern char __fastcall FUN_008ae710(int param); // Gets a flag or type
extern int __fastcall FUN_00983b20(int param); // Gets another property
extern int __fastcall FUN_008a5f60(int param); // Gets a value (maybe discount or special)
extern int __fastcall FUN_00983690(const void* a, const void* b); // Comparator for qsort (address 0x00983690)

// Global data references (from Ghidra)
extern int* DAT_0112b9b4; // Pointer to some global state (e.g., GameManager)
extern int* DAT_012233a0; // Pointer to another global (e.g., StoreManager singleton)

// Function pointer for iterator (likely a virtual function or callback)
extern void* (__fastcall *PTR_FUN_00e35c28)(); // Gets next element in iteration
extern void (__fastcall *_UNK_00e35c2c)(); // Advances iterator

// Structure for an item entry in the list (size 0x28 = 40 bytes)
struct ItemEntry {
    int field_0;      // +0x00: some ID or pointer
    int field_4;      // +0x04: unknown
    int field_8;      // +0x08: unknown (maybe type)
    short field_C;    // +0x0C: short value (e.g., price)
    char field_E;     // +0x0E: byte flag
    // ... remaining fields up to 0x28
};

// Main function: builds a sorted list of items from the store
void __fastcall StoreManager::buildSortedItemList(int this) // this in ECX
{
    int iVar1;
    int iVar2;
    char uVar3;
    short sVar4;
    ItemEntry* puVar5;
    ItemEntry* puVar6;
    int uVar7;
    int local_18; // counter
    int local_4;  // iterator pointer

    // Access global state
    iVar1 = *(int*)(DAT_0112b9b4 + 0x40); // +0x40 offset in global
    iVar2 = **(int**)(DAT_012233a0 + 4);  // Dereference pointer at +4

    // If the pointer is valid and not a sentinel (0x1f30), copy a value
    if ((iVar2 != 0) && (iVar2 != 0x1f30)) {
        *(int*)(this + 0x70) = *(int*)(iVar2 + -0x3c); // Copy from offset -0x3c (likely a parent or owner)
    }

    // Get some state byte and store it
    uVar3 = FUN_0089c630();
    *(char*)(this + 0x6c) = uVar3;

    // Check game state: iVar1 points to something with +0xd8 indicating state (2 or 3 = in-game?)
    if ((iVar1 != 0) && ((iVar1 = *(int*)(iVar1 + 0xd8), iVar1 == 2 || (iVar1 == 3)))) {
        // Get iterator pointer from this+0x64 (100 decimal)
        local_4 = *(int*)(this + 100);
        // If null or its +8 is null, reset to 0
        if ((local_4 == 0) || (*(int*)(local_4 + 8) == 0)) {
            local_4 = 0;
        }

        // Reset the iteration (maybe rewind)
        FUN_009842e0();

        local_18 = 0; // item count
        while (local_4 != 0) {
            // Get next element from the iterator
            puVar5 = (ItemEntry*)(*(code*)PTR_FUN_00e35c28)();

            // Check if the item is active (bit 0 of field at +0xc)
            if ((*(byte*)(puVar5 + 0xc) & 1) != 0) {
                // Allocate a new entry in the output list
                puVar6 = (ItemEntry*)FUN_00984440();

                // Convert item ID to short and store
                sVar4 = FUN_008a6320(puVar5[2]); // puVar5[2] is field at +8
                puVar6[5] = (int)sVar4; // +0x14? Actually puVar6[5] is offset 0x14 (5*4)

                // Get some property and set it
                uVar7 = FUN_004bb600(puVar5);
                FUN_004d3e20(uVar7);

                // Copy first field
                puVar6[0] = puVar5[0]; // +0x00

                // Copy another field
                puVar6[9] = puVar5[2]; // +0x24 (9*4)

                // Get a byte flag and store
                uVar3 = FUN_008ae710(puVar5[2]);
                *(char*)(puVar6 + 8) = uVar3; // +0x20? Actually puVar6+8 is offset 0x20 (8*4) but char? Might be misaligned

                // Get another property
                uVar7 = FUN_00983b20(puVar5[2]);
                puVar6[6] = uVar7; // +0x18

                // Check bit 1 of field at +0xc (shifted right by 1)
                if (((uint)puVar5[0xc] >> 1 & 1) == 0) {
                    uVar7 = FUN_008a5f60(puVar5[2]);
                } else {
                    uVar7 = 0;
                }
                local_18 = local_18 + 1;
                puVar6[7] = uVar7; // +0x1c

                // Store the bit flag at offset +0x21 (33 decimal)
                *(byte*)((int)puVar6 + 0x21) = (byte)((uint)puVar5[0xc] >> 1) & 1;
            }
            // Advance iterator
            (*_UNK_00e35c2c)();
        }

        // Store the count of items
        *(int*)(this + 0xb4) = local_18;

        // If more than one item, sort the list (each entry size 0x28)
        if (1 < *(uint*)(this + 0xbc)) {
            qsort(*(void**)(this + 0xb8), *(uint*)(this + 0xbc), 0x28,
                  (int (*)(const void*, const void*))&FUN_00983690);
        }
    }
    return;
}