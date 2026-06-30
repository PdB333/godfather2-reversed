// FUNC_NAME: GameManager::~GameManager
void __thiscall GameManager::destructor(GameManager* this) {
    // +0x00: vtable pointer
    *this = &PTR_FUN_00e30bb4;
    // +0x0C: pointer to a secondary structure (possibly an embedded manager)
    this->field_0x0C = &PTR_LAB_00e30bc4;

    // Call virtual cleanup or subsystem shutdown
    cleanupSubsystems();  // translates: FUN_00426000()

    // Check if a sub-object was allocated at +0x10
    if (this->pSubObject != 0) {
        // Deallocate memory of size 0x1D0 with associated destructor at 0x004a1830
        customFree(this->pSubObject, 0x1D0, *(uint32_t*)(this->pSubObject + -0x10), &LAB_004a1830);
        // Call specific destructor for the buffer
        bufferDestructor(this->pSubObject + -0x10);  // adjusts pointer by -0x10
    }
    this->pSubObject = 0;  // clear pointer

    // Release two global singleton buffers
    releaseGlobalBuffer(&g_globalBuffer1);  // DAT_012069d4
    releaseGlobalBuffer(&g_globalBuffer2);  // DAT_012069ec

    // Update virtual pointer to "destroyed" state
    this->field_0x0C = &PTR_LAB_00e30bc8;

    // Clear global initialization flag
    g_initialized = 0;  // DAT_0122339c

    // Final deinitialization call
    shutdownGlobals();  // FUN_004083d0()
}