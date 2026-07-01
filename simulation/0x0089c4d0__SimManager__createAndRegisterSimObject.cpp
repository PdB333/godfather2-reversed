// FUNC_NAME: SimManager::createAndRegisterSimObject
// Function at 0x0089c4d0
// Creates a SimObject (0x40 bytes), initializes it from a prototype, sets the field at +0x38,
// and registers it with the manager. Falls back to storing data globally if allocation fails.

void SimManager::createAndRegisterSimObject(uint prototype, uint data) {
    // Check if the sim system is active (FUN_00481640)
    if (!SimManager::isInitialized()) {
        return;
    }

    // Allocate 0x40 bytes for the new SimObject (FUN_009c8e50)
    SimObject* obj = static_cast<SimObject*>(SimManager::allocateMemory(0x40));
    if (obj != nullptr) {
        // Construct the object from the given prototype (FUN_0089c380)
        obj = SimManager::constructFromPrototype(prototype);
        // Store additional data at offset +0x38 (e.g., an ID or pointer to parent)
        obj->field_0x38 = data;
        // Register the object (add to active list, etc.) (FUN_00481690)
        SimManager::registerSimObject(obj);
    } else {
        // Allocation failed: use global fallback
        g_fallbackSimObject = data;  // _DAT_00000038
        SimManager::registerSimObject(nullptr);
    }
}