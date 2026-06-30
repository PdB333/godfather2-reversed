// FUNC_NAME: activateObject
// Function at 0x005e3c00: Global utility that activates a game object through a singleton manager's virtual method.
// Calls vtable index 1 (second method) on the object pointed by (DAT_01223518 + 4) with (object, 0) arguments.
// Returns 1 on success, 0 if manager or object is null.

extern void* DAT_01223518; // Global singleton pointer (e.g., g_pGameManager)

int __cdecl activateObject(void* pObject)
{
    int bSuccess = 0;
    // Manager's vtable pointer is stored at offset +0x04 from the global
    void** ppVtable = *(void***)((unsigned char*)DAT_01223518 + 4);
    if (ppVtable != 0 && pObject != 0)
    {
        // vtable[1] is the second method (offset 4 bytes)
        void (*activateMethod)(void*, int) = (void (*)(void*, int))ppVtable[1];
        activateMethod(pObject, 0); // Second argument 0 likely means "activate"
        bSuccess = 1;
    }
    return bSuccess;
}