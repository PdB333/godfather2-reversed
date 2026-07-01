// FUNC_NAME: SomeManager::~SomeManager
void __thiscall SomeManager::~SomeManager() {
    // vtable override for destruction phase
    *this = &PTR_FUN_00d72e60;                         // +0x00: set vtable to destruction vtable
    this->field3 = &PTR_LAB_00d72e5c;                  // +0x0C: set some function pointer

    // cleanup static subsystem
    shutdownSubsystemA(&DAT_0112da38);                 // FUN_004086d0
    shutdownSubsystemB(&DAT_0112da38);                 // FUN_00408310

    // free internal pointer if present
    if (this->field4 != NULL) {                        // +0x10: pointer to dynamically allocated resource
        deleteResource(this->field4);                   // FUN_009c8f10
    }

    // final destruction step
    this->field3 = &PTR_LAB_00d72e48;                  // +0x0C: update pointer
    g_globalInitFlag = 0;                               // DAT_01129918: flag indicating initialized state
    cleanupCore();                                      // FUN_004083d0
}