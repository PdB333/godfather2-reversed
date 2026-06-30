// FUNC_NAME: GetComponentFromHandle
// Function address: 0x005e9780
// Purpose: Retrieves an object/component handle via the game manager if the source object's component pointer is valid.
// Returns 0xFFFFFFFF ( -1 ) on failure, else the result of the manager's call.
//
// Offsets relative to param_2 (likely a Sentient/NPC object):
//   +0x484: m_componentPtr (pointer to a component, non-null indicates validity)
//   +0x1cc: m_componentHandle (handle/ID to pass to the game manager)

// The global pointer to the game manager singleton (vtable-based)
// Address 0x01223510 stores a pointer to the manager instance
extern void* gGameManager;

// Typedef for the method at vtable offset 0x68 – takes a handle and returns some object pointer
typedef uint (__thiscall* GetObjectByHandleFn)(void* manager, uint handle);

uint __fastcall GetComponentFromHandle(uint /*unused*/, int param2) {
    uint result = 0xFFFFFFFF; // Default failure value

    // Check if the component pointer at +0x484 is valid (non-null)
    if (*(int*)(param2 + 0x484) != 0) {
        // Retrieve the game manager instance from the global pointer
        void* manager = *(void**)gGameManager;

        // Get the function pointer at vtable offset 0x68
        GetObjectByHandleFn func = (GetObjectByHandleFn)(*(void**)((char*)manager + 0x68));

        // Call with the handle stored at param2 + 0x1cc
        result = func(manager, *(uint*)(param2 + 0x1cc));
    }

    return result;
}