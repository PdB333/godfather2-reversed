// FUNC_NAME: GodfatherGameManager::createPlacementObject
void __thiscall GodfatherGameManager::createPlacementObject(
    uint32 param_1, // this pointer (manager)
    uint32 param_2, // unused? possibly index
    uint32 param_3, // x or offset1
    uint32 param_4, // y or offset2
    uint32 param_5, // z or offset3
    uint32 param_6, // data1
    uint32 param_7, // data2
    uint32 param_8, // data3
    uint32 param_9  // data4
) {
    // Check if game is active (likely a singleton check)
    bool isActive = FUN_00481640();
    if (isActive) {
        // Allocate a block of size 0x58 (88 bytes) – probably a new object
        uint32 obj = FUN_009c8e50(0x58);
        if (obj == 0) {
            obj = 0; // allocation failed
        } else {
            // Call constructor on the allocated memory, passing the manager as parent/reference
            FUN_008a9de0(obj); // likely initializes base data
            // Fill the object's fields at fixed offsets
            // +0x3c: coordinate/dimension 1
            *(uint32*)(obj + 0x3c) = param_3;
            // +0x44: coordinate/dimension 3
            *(uint32*)(obj + 0x44) = param_5;
            // +0x40: coordinate/dimension 2
            *(uint32*)(obj + 0x40) = param_4;
            // +0x4c: data field 2
            *(uint32*)(obj + 0x4c) = param_7;
            // +0x48: data field 1
            *(uint32*)(obj + 0x48) = param_6;
            // +0x54: data field 4
            *(uint32*)(obj + 0x54) = param_9;
            // +0x50: data field 3
            *(uint32*)(obj + 0x50) = param_8;
        }
        // Register the object with the game manager (or add to list)
        FUN_00481690(obj);
    }
}