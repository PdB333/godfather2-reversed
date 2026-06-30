// FUNC_NAME: HandleManager::releaseHandle
// Address: 0x005e3c00
// This function releases a handle (presumably to an object) via a global manager.
// It checks if the global handle manager is initialized and if the handle is valid.
// If so, it calls a virtual function (vtable offset 4) on the manager to release the handle,
// passing a flag of 0 (maybe indicating normal release). Returns 1 if action taken, else 0.

// Global pointer to handle manager singleton (offset from DAT_01223518 gives pointer to manager object)
extern HandleManager* g_pHandleManager; // actual address: DAT_01223518 + 0x4

// The handle manager class (size unknown)
class HandleManager {
public:
    // vtable: index 0 likely queryInterface/AddRef
    // vtable index 1 (offset 4): releaseObject / releaseHandle
    virtual void releaseObject(int handle, int flags); // __thiscall
};

// Implementation of the global function
int releaseHandle(int handle) {
    if (g_pHandleManager != nullptr && handle != 0) {
        g_pHandleManager->releaseObject(handle, 0);
        return 1;
    }
    return 0;
}