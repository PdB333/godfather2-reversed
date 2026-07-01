// FUNC_NAME: SimManager::SimManager
// Address: 0x007df090
// Role: Constructor for SimManager, initializes base/derived vtables, registers with a global manager, clears initialization flag.

__thiscall SimManager::SimManager(SimManager *this) {
    // Set base class virtual table (class hierarchy base)
    this->vtable = &PTR_LAB_00d6f784;   // base vtable

    // Retrieve a pointer to a major global manager (e.g., GameManager, InputDeviceManager)
    int *globalMgr = (int *)GetGlobalManagerSingleton(); // FUN_007ab150

    // Invoke a method via the global manager's vtable at index 1.
    // This likely registers this object's callback ID (stored at this+0x74) with the manager.
    (**(code **)(globalMgr[0] + 4))(this->field_0x1d);   // param_1[0x1d] = callback id

    // Clear the highest bit (bit 31) of a flag stored in a large global structure.
    // This marks a subsystem as initialized/clean.
    uint32_t *initFlag = (uint32_t *)(this->globalStatePtr + 0x249c); // param_1[0x16] = pointer to large state
    *initFlag &= 0x7fffffff;

    // Logging or debug output using argument 0.
    LogDebug(0); // FUN_0045f2a0

    // Switch to derived class virtual table.
    this->vtable = &PTR_LAB_00d6b95c;   // derived vtable

    // Perform additional derived-class initialization.
    InitializeSubsystem(); // FUN_0080ea60

    // Conditional cleanup/destruction path.
    // In debug builds, the low bit of the return address may be set for stack‑constructed objects.
    if ((unaff_retaddr & 1) != 0) {
        CleanupAndDestroy(this); // FUN_00624da0
    }
}