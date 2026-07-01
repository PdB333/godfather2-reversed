// FUNC_NAME: ComponentManager::getComponentForObject
// Function at 0x007b9a20 - Attempts to retrieve a component from an object via interface query.
// Uses a virtual QueryInterface (vtable+0x10) with hash 0x369ac561 to test for a specific component type.
// On success, validates manager state and calls internal retrieval function.
int __thiscall ComponentManager::getComponentForObject(int *objectPtr) {
    int *originalObjectPtr = objectPtr;          // Save original pointer
    int *interfaceOut = nullptr;                 // Output pointer for QueryInterface

    if (objectPtr != nullptr) {
        int *vtable = *(int **)objectPtr;        // +0x00 vtable pointer
        // QueryInterface (__thiscall on objectPtr) with constant hash and output pointer
        bool interfaceFound = (**(bool (__thiscall **)(void*, unsigned int, int**))(vtable + 0x10))
                              (objectPtr, 0x369ac561, &interfaceOut);
        // unaff_retaddr condition (likely m_bInitialized member)
        if (interfaceFound && this->m_bInitialized) {
            if (this->isReady()) {               // FUN_00734340(this)
                return this->getComponentData(originalObjectPtr); // FUN_007b5430(this, originalPtr)
            }
        }
    }
    return 0;
}