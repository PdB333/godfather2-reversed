// FUNC_NAME: ComponentManager::registerComponent
// Function address: 0x0097f7c0
// Role: Registers a component/entity with the manager, storing its ID and a handle.
// Calls virtual function at vtable+0x6c (likely onRegister or onActivate).
// Uses FUN_0097f740 to obtain an ID from a pool (returns -1 on failure).
// On success, stores ID at this+0x60 and handle from param_2+0x54 at this+0x11C.
// Returns success flag (low byte = 1) combined with handle upper bits.

uint __thiscall ComponentManager::registerComponent(int *this, int *component) {
    int handle;
    uint id;

    if (component != 0) {
        // Call virtual function at vtable offset 0x6c (e.g., onRegister)
        (**(code **)(*this + 0x6c))();
        
        id = FUN_0097f740(component); // Get a unique ID from pool
        if (id != 0xffffffff) {
            this[0x18] = id;          // Store ID at offset 0x60 (this+0x60)
            handle = *(int *)(component + 0x54); // Read handle from component+0x54
            this[0x47] = handle;      // Store handle at offset 0x11C (this+0x11C)
            // Return success: low byte = 1, high 3 bytes = handle >> 8
            return (handle & 0xFFFFFF00) | 1;
        }
    }
    // Failure: return id with low byte cleared
    return id & 0xFFFFFF00;
}