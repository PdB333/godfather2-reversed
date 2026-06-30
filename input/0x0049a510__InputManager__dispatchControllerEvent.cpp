// FUNC_NAME: InputManager::dispatchControllerEvent
// Address: 0x0049a510
// This function is part of the input system. It calls a virtual method on a delegate object (at this+0x4) 
// and uses the returned byte to dispatch a handler from a global table.
//
// The global variables:
//   g_handlerTableSize (DAT_01217d80) - number of handlers
//   g_handlerTable (DAT_01217d84) - array of function pointers (each 4 bytes) indexed by (returned_byte - 1)
//
// Note: The decompiler incorrectly multiplied the index by 2; we assume 4-byte pointers.

#include <cstdint>

// Forward declaration of the global table
extern int g_handlerTableSize;          // DAT_01217d80
extern void (*g_handlerTable[])(void); // DAT_01217d84

void __fastcall InputManager::dispatchControllerEvent(void* thisPtr, uint32_t param2)
{
    // Get the delegate object at offset +0x4 (e.g., an IControllerHandler)
    void* delegate = *(void**)((char*)thisPtr + 4); // +0x4

    // Call virtual function at vtable offset 0xC (function index 3)
    // The function returns a code byte (likely an event ID)
    typedef uint8_t (__fastcall *VFunc)(void*, uint32_t);
    VFunc vfunc = *(VFunc*)(*(uintptr_t*)delegate + 0xC);
    uint8_t code = vfunc(delegate, param2);

    // Check if the code is valid (1-based index)
    if ((uint32_t)(code - 1) < (uint32_t)g_handlerTableSize)
    {
        // Dispatch to the registered handler
        g_handlerTable[code - 1]();
    }
    // If code == 0, subtraction yields 0xFF which is >= g_handlerTableSize, so no dispatch.
}