// FUNC_NAME: InputManager::dispatchToController
// Purpose: Dispatches to one of two controller handlers based on an index passed in EAX.
// The index must be 0 or 1; otherwise the call is ignored.
// Controllers are stored as an array of pointers at offset +0x08 from this.
void __thiscall InputManager::dispatchToController(int param2, int param3, int param4, int param5, int param6)
{
    // The controller index is passed in EAX register (uint in_EAX).
    // In the original binary this was not a parameter but a register value.
    // Reconstructed as: uint controllerIndex = in_EAX;
    // For clarity we assume it is the first parameter after this, but the original used EAX.
    // We treat it as a hidden parameter.
    uint controllerIndex = /* in_EAX */ 0; // Placeholder: actual value from register

    // Validate index: must be 0 or 1 (two slots)
    if (controllerIndex < 2)
    {
        // Retrieve the controller pointer from the array at this+0x08
        // Each entry is 4 bytes (pointer to Controller object)
        // +0x08: m_pControllers[0], +0x0C: m_pControllers[1]
        void *pController = *(void **)(this + 8 + controllerIndex * 4);

        // Call the handler function (FUN_004587c0) on the selected controller
        // The controller object is passed as the implicit this pointer
        FUN_004587c0(pController, param2, param3, param4, param5, param6);
    }
    // If index >= 2, do nothing (safe guard)
}