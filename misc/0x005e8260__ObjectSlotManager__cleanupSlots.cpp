// FUNC_NAME: ObjectSlotManager::cleanupSlots

void __thiscall ObjectSlotManager::cleanupSlots()
{
    // First, handle the single object pointer at +0x494 with functor at +0x4a0
    if (*(int*)(this + 0x494) != 0) {
        (*(void (__thiscall**)(int))(this + 0x4a0))(*(int*)(this + 0x494));
    }

    // Iterate over 4 groups of 5 object pointers, stored in reverse order
    // Each group occupies 0x6c (108) bytes
    int* piVar3 = (int*)(this + 0x1b4);
    int iVar1 = 3;
    undefined4* puVar2 = (undefined4*)(this + 0x1f0);

    do {
        piVar3 -= 0x1b;          // Move to previous group's last object pointer
        puVar2 -= 0x1b;          // Move to previous group's base

        // Group contains 5 slots, each with object pointer and destructor function pointer
        // Slots are stored in order: objectPtr, destructorFunc, objectPtr, destructorFunc, ...
        // Offsets relative to puVar2 (base of group):
        // Slot 0: objectPtr at -0x1a, destructor at -0x17
        if (puVar2[-0x1a] != 0) {
            (*(code*)puVar2[-0x17])(puVar2[-0x1a]);
        }
        // Slot 1: objectPtr at -0x1e, destructor at -0x1b
        if (puVar2[-0x1e] != 0) {
            (*(code*)puVar2[-0x1b])(puVar2[-0x1e]);
        }
        // Slot 2: objectPtr at -0x22, destructor at -0x1f
        if (puVar2[-0x22] != 0) {
            (*(code*)puVar2[-0x1f])(puVar2[-0x22]);
        }
        // Slot 3: objectPtr at -0x26, destructor at -0x23
        if (puVar2[-0x26] != 0) {
            (*(code*)puVar2[-0x23])(puVar2[-0x26]);
        }
        // Slot 4: objectPtr from separate pointer piVar3, destructor at -0x27
        if (*piVar3 != 0) {
            (*(code*)puVar2[-0x27])(*piVar3);
        }

        iVar1--;
    } while (iVar1 >= 0);
}