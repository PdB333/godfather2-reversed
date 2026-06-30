// FUNC_NAME: SimManager::~SimManager
// Address: 0x006a83f0
// Destructor for SimManager. Cleans up resources, releases a global mutex, 
// and resets the global reference count to zero.
void __thiscall SimManager::~SimManager() {
    // Set primary vtable to destructor vtable (points to base class cleanup)
    this->vtable = (void**)&SimManager_vtable_dtor; // +0x00: PTR_FUN_00d5d8b8

    // Set secondary vtable pointer (likely for another base class)
    this->field_0C = (void**)&SimManager_base1_vtable; // +0x0C: PTR_LAB_00d5d8b4

    // Release global mutex / decrement reference count for the singleton
    UnlockGlobalMutex(&g_simManagerMutex); // FUN_004086d0, &DAT_012069c4

    // Free the dynamically allocated member if present (e.g., an allocated buffer)
    if (this->m_allocatedBuffer != nullptr) { // +0x14: param_1[5]
        DeleteAllocatedObject(this->m_allocatedBuffer); // FUN_004daf90
    }

    // Reassign secondary vtable to another base (virtual inheritance chain)
    this->field_0C = (void**)&SimManager_base2_vtable; // +0x0C: PTR_LAB_00d5d898

    // Reset global reference count to zero (indicating no active instances)
    g_simManagerRefCount = 0; // DAT_011299b4

    // Perform final global cleanup (e.g., release static resources)
    FinalCleanupGlobal(); // FUN_004083d0
}