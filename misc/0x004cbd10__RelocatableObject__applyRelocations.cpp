// FUNC_NAME: RelocatableObject::applyRelocations
// Address: 0x004cbd10
// Reconstructed constructor-like function that sets vtable and applies self-relative pointer fixups
// from a relocation table stored at offset +0x08. This is typical of EA EARS engine objects
// that are loaded as blobs and need internal pointer adjustments.

// Structure of the object: (offsets from 'this')
// +0x00: vtable pointer
// +0x04: some field (set to 0)
// +0x08: pointer to relocation data (if non-null, contains table for fixups)

// Relocation data structure (pointed by this+0x08):
// +0x00: unknown (unused here)
// +0x04: uint32 count of sub-object pointers
// +0x08: array of uint32 pointers to sub-objects (each pointer is relative to this base)

void __thiscall RelocatableObject::applyRelocations(void) {
    int *thisPtr = (int *)this; // assume int size for pointer
    int iVar1;
    uint uVar2;
    int iVar3;
    uint uVar4;

    // Initialize vtable and a field
    thisPtr[1] = 0;                                    // +0x04 = 0
    *thisPtr = (int)&PTR_FUN_00e3666c;                // +0x00 vtable pointer

    // Fixup the relocation data pointer itself (self-relative)
    if (thisPtr[2] != 0) {
        thisPtr[2] = thisPtr[2] + (int)thisPtr;       // +0x08 becomes absolute
    }

    iVar1 = thisPtr[2]; // relocation data pointer
    if (iVar1 != 0) {
        // Fixup the array pointer within relocation data
        if (*(int *)(iVar1 + 8) != 0) {
            *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) + (int)thisPtr; // make absolute
        }

        // Number of sub-objects to fix
        uVar2 = *(uint *)(iVar1 + 4); // count at +0x04 of relocation data
        uVar4 = 0;
        if (uVar2 != 0) {
            do {
                // Adjust each sub-object pointer in the array
                int *arrayBase = *(int **)(iVar1 + 8); // array of pointers (already absolute)
                iVar3 = arrayBase[uVar4]; // original relative pointer
                if (iVar3 != 0) {
                    arrayBase[uVar4] = iVar3 + (int)thisPtr; // make absolute
                }

                // Now fixup within that sub-object: its +0x68 pointer
                int subObjPtr = arrayBase[uVar4]; // absolute pointer to sub-object
                if (*(int *)(subObjPtr + 0x68) != 0) {
                    // Fix pointer at subObj+0x68: add subObj base
                    *(int *)(subObjPtr + 0x68) = *(int *)(subObjPtr + 0x68) + subObjPtr;
                }

                // Then fixup within that secondary pointer at +4
                iVar3 = *(int *)(subObjPtr + 0x68);
                if ((iVar3 != 0) && (*(int *)(iVar3 + 4) != 0)) {
                    *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + subObjPtr;
                }

                uVar4 = uVar4 + 1;
            } while (uVar4 < uVar2);
        }
    }
    return;
}