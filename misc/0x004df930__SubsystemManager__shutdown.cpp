// FUNC_NAME: SubsystemManager::shutdown
// Function address: 0x004df930 — Deinitialization/shutdown routine for a subsystem manager (e.g., input, audio). Uses a global singleton pointer (DAT_012054c0) to manage resources. Calls a check function (isSubsystemActive) and, if active, stops the subsystem. If the reference count at offset +0x4 is zero, frees a pointer at offset +0x0 and clears offsets +0x0 and +0x8.

void __thiscall SubsystemManager::shutdown(void)
{
    // Global pointer to the subsystem manager singleton (offsets: +0x0 = allocated memory, +0x4 = ref count, +0x8 = extra field)
    int* pGlobalManager = (int*)DAT_012054c0;
    // Check if the subsystem is active; returns >=0 if active, <0 if not
    int iActiveStatus = isSubsystemActive(this);
    if (iActiveStatus >= 0) {
        stopSubsystem(); // Stop the subsystem (e.g., release resources, stop threads)
    }
    // If reference count at offset +0x4 is zero, deallocate resources
    if (pGlobalManager[1] == 0) {
        pGlobalManager[1] = 0; // Redundant assignment
        freePointer((void*)pGlobalManager[0]); // Free the memory pointed to by offset +0x0
        pGlobalManager[0] = 0; // Clear the pointer
        pGlobalManager[2] = 0; // Clear the extra field
    }
    return;
}