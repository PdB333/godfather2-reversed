// FUNC_NAME: EntityManager::updateChildFlags
void __fastcall EntityManager::updateChildFlags(EntityManager* this) {
    uint* flagsThis = (uint*)((int)this + 0x34);
    // Check if bit 4 is already set in this object's flags
    if ((*flagsThis >> 4 & 1) == 0) {
        // Set bit 4 (0x10) to mark that this update has been performed
        *flagsThis = *flagsThis | 0x10;

        // Get the pointer at +0x10 (likely a world/scene object)
        int* worldPtr = *(int**)((int)this + 0x10);
        // Check if the world's +0xD4 field is zero (e.g., world not active)
        if (worldPtr != nullptr) {
            int worldActiveFlag = *(int*)((int)worldPtr + 0xD4);
            if (worldActiveFlag == 0) {
                uint childCount = *(uint*)((int)this + 0x20);
                if (childCount != 0) {
                    uint index = 0;
                    do {
                        // Get pointer to child object from array at +0x1C
                        int* child = *(int**)(*(int*)((int)this + 0x1C) + index * 4);
                        // Call a random/condition function (might be time-based or random)
                        char conditionResult = FUN_00791230();  // e.g., randomCheck()
                        if (conditionResult != 0) {
                            uint* childFlags = (uint*)((int)child + 0x5C);
                            // Check if bit 20 (0x100000) is not set
                            if ((*childFlags >> 0x14 & 1) == 0) {
                                // Set bit 23 (0x800000) on the child
                                *childFlags = *childFlags | 0x800000;
                            }
                        }
                        index++;
                    } while (index < childCount);
                }
            }
        }
    }
}