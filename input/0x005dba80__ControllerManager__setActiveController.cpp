// FUNC_NAME: ControllerManager::setActiveController
// Address: 0x005dba80
// Sets this controller as the active one. If already active, deactivates it.
// Global DAT_012058e8 stores pointer to current active controller.

extern void* g_activeController; // DAT_012058e8

void __fastcall ControllerManager::setActiveController(int this) {
    if (g_activeController != reinterpret_cast<void*>(this)) {
        // Mark this controller as active
        *reinterpret_cast<int*>(this + 0xa4) = 1; // active flag
        g_activeController = reinterpret_cast<void*>(this);
        // Enable two sub-components (likely input port handlers)
        FUN_0060a460(*reinterpret_cast<int*>(this + 0x10)); // sub-component 1
        FUN_0060a460(*reinterpret_cast<int*>(this + 0x14)); // sub-component 2
    } else {
        // Already active, so deactivate it
        *reinterpret_cast<int*>(this + 0xa4) = 0;
    }
}