// FUNC_NAME: SimManager::update
// Function address: 0x004cb9e0
// Role: Main simulation update tick with reentrancy guard and virtual call
// Global gSimUpdateLockCount (_DAT_01205a30) is a reentrancy counter for the update loop.
// Calls a virtual method at vtable offset 0x0C (4th virtual) on the SimManager instance.
// Also checks if simulation is paused (FUN_00655250) and if not, calls a processing function (FUN_00655130).

void __thiscall SimManager::update(void) {
    int* thisPtr; // in_EAX
    bool paused;

    gSimUpdateLockCount++; // increment reentrancy guard

    // htonl(0) - possibly a debug placeholder or no-op barrier (common in EA EARS engine)
    htonl(0);

    // Call virtual function at vtable offset 0x0C (e.g., "onUpdate" or "processSimulation")
    (*(void (__thiscall**)(void*))(*(int*)thisPtr + 0x0C))(thisPtr);

    // Check pause state; if not paused, perform additional processing
    paused = (FUN_00655250() != 0);
    if (!paused) {
        FUN_00655130(); // e.g., "processFrame" or "updateEntities"
    }

    gSimUpdateLockCount--; // decrement guard
}