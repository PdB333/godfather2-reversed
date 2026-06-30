// FUNC_NAME: getGlobalProperty
// Function address: 0x005e6aa0
// Role: Retrieves a specific uint32 value from a global manager using a hardcoded key (0).
//       The global manager is referenced via DAT_01223514. The callee (0x005f0600) takes the
//       manager pointer and a key pointer, returning a pointer to the value.
//       This function dereferences that pointer or returns 0 if null.

#include <cstdint>

// External global manager pointer (likely a singleton)
extern void* g_globalManager;

// External lookup function that returns a pointer to a value for the given key.
// The key is a uint8_t (passed by pointer) and the returned pointer points to a uint32_t.
extern uint32_t* ManagerLookup(void* manager, uint8_t* key);

uint32_t getGlobalProperty()
{
    uint8_t key = 0;                     // Hardcoded key value (index 0)
    uint32_t* valuePtr = ManagerLookup(g_globalManager, &key);
    if (valuePtr != nullptr)
    {
        return *valuePtr;                // Return the dereferenced value
    }
    return 0;                            // Fallback if lookup fails
}