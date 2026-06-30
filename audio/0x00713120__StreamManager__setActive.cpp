// FUNC_NAME: StreamManager::setActive
// Address: 0x00713120
// This function toggles the active state of a stream (e.g., audio master). When activated,
// it acquires global locks and stores a global stream handle. When deactivated, it releases them.
// The check at this+0x10 likely indicates whether the stream object (or its owner) exists.

void __thiscall StreamManager::setActive(bool isActive)
{
    // Apply the active state change (e.g., adjust volume, priority, or other flags)
    FUN_00721350(isActive);

    // Only proceed if the stream pointer exists (offset +0x10)
    if (*(int*)(this + 0x10) != 0) {
        if (isActive) {
            // Acquire global resources (likely mutexes or reference counts)
            FUN_004086d0(&DAT_0112dd08);  // +0x0: unknown global object
            FUN_004086d0(&DAT_0112ac90);  // +0x0: unknown global object
            // Store a global master stream handle into local field
            *(int*)(this + 0x38) = DAT_00d5ccf8;  // +0x38: active stream reference
        } else {
            // Release global resources
            FUN_00408680(&DAT_0112dd08);
            FUN_00408680(&DAT_0112ac90);
        }
    }
    return;
}