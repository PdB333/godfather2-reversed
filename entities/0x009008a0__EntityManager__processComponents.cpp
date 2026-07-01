// FUNC_NAME: EntityManager::processComponents
// Function address: 0x009008a0
// Decompiled from The Godfather 2 (2008, PC, EA EARS engine)

void __fastcall EntityManager::processComponents(int* this)
{
    ushort flags = *(ushort*)(this + 0x60);  // +0x60: state flags (ushort)

    // Check if bit 0 (kFlagActive) is set
    if ((flags & 1) != 0) {
        // Clear bit 0 and bits 12,13 (kFlagInit, kFlagProcessing? )
        *(ushort*)(this + 0x60) = flags & 0xcffe;

        // If bits 12,13 were set, call vtable method at offset 0x18 (likely initialize/reset)
        if ((flags & 0x3000) != 0) {
            (**(code**)(*(int*)this + 0x18))();
        }

        // Release resource or handle at +0x61 (offset 0x184)
        FUN_00851230(this[0x61]);

        // Clear bits 10,11 (0x400, 0x800) in flags
        *(ushort*)(this + 0x60) = *(ushort*)(this + 0x60) & 0xf3ff;

        // Pointer to a component list (+0x74, offset 0x1D0)
        undefined4* componentList = (undefined4*)this[0x74];
        if (componentList != (undefined4*)0x0) {
            int componentCount = componentList[1];  // number of components
            // Check if bit 3 (kFlagComponentActive) set and there are components
            if (((*(ushort*)(this + 0x60) & 8) != 0) && (componentCount != 0)) {
                int* componentArray = (int*)*componentList;  // base pointer to component array (each 12 bytes)
                do {
                    int* currentComponent = componentArray;
                    if ((*currentComponent != 0) && (int* basePtr = *currentComponent + -0x48, basePtr != 0)) {
                        // Call per-component cleanup via vtable at offset 0x154
                        (**(code**)(*(int*)this + 0x154))(basePtr);
                    }
                    componentArray = componentArray + 3;  // 3 ints per component (12 bytes)
                    componentCount--;
                } while (componentCount != 0);
            }

            // Notify listeners or clear two event queues (pass 0 as argument)
            FUN_00900650(0);
            FUN_00900650(0);
        }
    }
}