// FUNC_NAME: callGlobalVtableMethod
// Function address: 0x005e3d90
// This function ignores its own `this` pointer (if any) and calls a virtual method at offset 0xBC
// on a global object pointed to by `g_globalObject` (address 0x01223510).
// Typically used to forward calls to a singleton manager.

void __thiscall callGlobalVtableMethod(void* this, int arg1, int arg2)
{
    // Global singleton pointer stored at 0x01223510
    extern void* g_globalObject;

    // Fetch vtable pointer from the object
    void** vtable = *(void***)g_globalObject;

    // Function pointer at vtable offset 0xBC (index 47 for 32-bit pointers)
    typedef void (__thiscall* VFunc)(void*, int, int);
    VFunc method = (VFunc)vtable[0xBC / 4];

    // Call the virtual method on the global object
    method(g_globalObject, arg1, arg2);
}