// FUNC_NAME: SimManager::createSimObject

void __thiscall SimManager::createSimObject(int someValue) {
    // Check if the game is ready/systems initialized
    if (!isGameReady()) {
        return;
    }

    // Allocate memory for the new object (size 0x40 = 64 bytes)
    int* newObj = (int*)allocateMemory(0x40);
    if (newObj != nullptr) {
        // Construct the object, associating it with this SimManager
        newObj = (int*)constructObject(this);
        // Store the provided value at offset +0x38 (likely an ID or reference)
        newObj[0x38 / 4] = someValue;  // +0x38
        // Register the object into the manager's list/collection
        registerObject(newObj);
    } else {
        // Allocation failed – store the value in a global fallback variable
        g_lastFailedValue = someValue;
        // Register null to indicate failure
        registerObject(nullptr);
    }
}