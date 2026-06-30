// FUNC_NAME: Dispatcher::processMessageOnID
#include <cstdint>

// Forward declaration of the helper function that resolves an identifier to an object pointer.
// Based on FUN_004dafd0 (likely resolves an ID to a pointer or handle).
extern void* __cdecl resolveObjectByID(int id);

// This is a member function of some class with a vtable.
// The virtual function at vtable+0xA8 (index 42) takes two arguments:
//   arg1: pointer to a resolved object (result of resolveObjectByID)
//   arg2: an additional integer/flag (likely message data)
// The function returns an undefined4 (uint32_t).
uint32_t __thiscall Dispatcher::processMessageOnID(int id, uint32_t data)
{
    uint32_t result = 0;

    // Only proceed if the identifier is valid (non-zero).
    if (id != 0)
    {
        // Resolve the identifier to an object pointer/handle.
        void* resolvedObj = resolveObjectByID(id);

        // Retrieve the virtual function at offset +0xA8 from the vtable of 'this'.
        // The vtable pointer is the first dword of the object.
        uint32_t (__thiscall *vfunc)(void*, uint32_t) =
            reinterpret_cast<uint32_t (__thiscall*)(void*, uint32_t)>(
                *reinterpret_cast<uint32_t*>(
                    *reinterpret_cast<uint32_t*>(this) + 0xA8
                )
            );

        // Call the virtual function with the resolved object and the data parameter.
        result = vfunc(resolvedObj, data);
    }

    return result;
}