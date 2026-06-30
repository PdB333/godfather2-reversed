// FUNC_NAME: Entity::getOwningEntityIfValid
// Address: 0x006e07b0
// This function checks if this->m_pChild (offset 0x31a8) is non-zero and if its containing object (at child - 0x48) supports a specific interface (hash 0xdc51ebb1)
// and is not filtered by a global state. Returns the containing object if valid, otherwise null.

int* Entity::getOwningEntityIfValid() {
    // Offset +0x31a8: pointer to a child structure (e.g., a component or linked node)
    if (this == 0) return 0;
    int* childPtr = *(int**)((int)this + 0x31a8);
    if (childPtr == 0) return 0;

    // The child is embedded in a container at offset -0x48 (probably a base object with a vtable)
    int* container = childPtr - 0x48 / sizeof(int);  // Equivalent to (int*)(childPtr - 0x12) but let's keep as byte offset.
    // Actually, subtract 0x48 bytes from the pointer.
    container = (int*)((int)childPtr - 0x48);

    if (container == 0) return 0;

    // Temporarily overwrite local variable with 0 for the interface check call.
    int dummy = 0;

    // Call virtual function at vtable+0x10 on the container object.
    // This function likely checks if the container implements a specific interface (hash 0xdc51ebb1).
    // The second parameter (address of dummy) may be filled with a result pointer, but here it's ignored.
    bool interfaceSupported = (**(code**)(*(int*)container + 0x10))(0xdc51ebb1, &dummy);

    if (interfaceSupported) {
        // unaff_ESI is likely a global pointer (e.g., current active player or controller).
        // In the original code, it's stored in ESI before call, possibly from the caller's context.
        extern int* g_pActiveController; // NOTE: unaff_ESI, uninitialized in this scope; assumed to be a global.
        if (g_pActiveController != 0) {
            // Call virtual function at vtable+0x38 on the global object.
            // This likely returns whether the active controller is in a state that filters out this container.
            bool isFiltered = (**(code**)(*(int*)g_pActiveController + 0x38))();
            if (isFiltered) {
                return 0;
            }
        }
        return container;
    }

    return 0;
}