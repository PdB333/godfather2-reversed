// FUNC_NAME: InputManager::dispatchInputToEntities
void InputManager::dispatchInputToEntities(int context, uint inputMask)
{
    // Check if there is any input to process
    if (inputMask == 0) {
        return;
    }

    // Get the vtable pointer from the singleton manager (e.g., GameManager)
    // If context is null, we don't have a valid target
    int* vtable = nullptr;
    if (context != 0) {
        vtable = (int*)FUN_0043b870(DAT_01131010); // getSingleton()->vtable
    }

    // Check if input processing is allowed (e.g., not in menu/cutscene)
    bool inputEnabled = (FUN_00481640() != 0); // returns char, treat as bool

    if (!inputEnabled) {
        // Normal mode: iterate over all registered input mappings
        // Each entry is 8 bytes: [uint id, uint mask]
        // Array at DAT_00d7a5c0 (IDs) and DAT_00d7a5c4 (masks) are interleaved
        for (uint i = 0; i < 0x58; i += 8) {
            uint entryMask = *(uint*)((int)&DAT_00d7a5c4 + i);
            if ((entryMask & inputMask) != 0) {
                uint entryId = *(uint*)((int)&DAT_00d7a5c0 + i);
                // Check if the object is valid (alive, exists)
                if (FUN_009add30(entryId) == 0) {
                    int* obj = (int*)FUN_009b9c00(entryId);
                    if (obj != 0) {
                        // Call virtual function at vtable offset 0x20 (index 8)
                        // This likely processes the input for that object
                        (**(code**)(*vtable + 0x20))(obj);
                    }
                }
            }
        }
    } else {
        // Special mode: only handle input flag 0x400 (e.g., "confirm" or "action")
        if ((inputMask & 0x400) != 0) {
            uint specialId = 0x1fe4b94e; // Fixed ID for a special object (e.g., player)
            if (FUN_009add30(specialId) == 0) {
                int* obj = (int*)FUN_009b9c00(specialId);
                if (obj != 0) {
                    // First call virtual function at vtable offset 0x1c (index 7) with context
                    (**(code**)(*vtable + 0x1c))(context);
                    // Then call virtual function at offset 0x20 with the object
                    (**(code**)(*vtable + 0x20))(obj);
                }
            }
        }
    }
}