// FUNC_NAME: Framework::SystemManager::~SystemManager
// Address: 0x006e79c0
// Role: Destructor, releases singleton instances, performs global cleanup

void __thiscall SystemManager::~SystemManager(void)
{
    // Set vtable pointers for destruction phase
    this->vtable = &PTR_FUN_00d5fb3c;         // +0x00: virtual table pointer
    this->field_04 = &PTR_LAB_00d5fb2c;       // +0x04: secondary vtable or pointer
    this->field_10 = &PTR_LAB_00d5fb20;       // +0x10: another function pointer

    // Release first singleton (e.g., AudioDataManager or StreamManager)
    if (DAT_0112a99c != nullptr)
    {
        releaseReference(*DAT_0112a99c);       // FUN_009c8f10 - decrement refcount / free internals
        deallocateMemory(DAT_0112a99c);        // FUN_009c8eb0 - operator delete
    }

    // Release second singleton (e.g., ControllerManager)
    if (DAT_0112a9a0 != nullptr)
    {
        destructComponent();                   // FUN_006e6cf0 - specialized destructor for this singleton
        releaseReference(*DAT_0112a9a0);       // FUN_009c8f10
        deallocateMemory(DAT_0112a9a0);        // FUN_009c8eb0
    }

    // Global cleanup routines
    globalCleanupPhaseA();                     // FUN_0049c640
    globalCleanupPhaseB();                     // FUN_004083d0

    // Set final vtable (base class / destroyed state)
    this->vtable = &PTR_LAB_00d5fb00;          // +0x00: vtable for fully destroyed object

    // Mark system as uninitialized
    DAT_011298a4 = 0;                          // global initialization flag

    return;
}