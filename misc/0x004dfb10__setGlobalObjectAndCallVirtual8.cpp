// FUNC_NAME: setGlobalObjectAndCallVirtual8
// Address: 0x004dfb10
// Role: Sets a global pointer to an object and calls its third virtual function (offset 8), then calls another function with the second argument (likely cleanup/initialization step).
void setGlobalObjectAndCallVirtual8(void* pObject, int arg2)
{
    // Store the pointer globally (e.g., singleton or current active instance)
    g_pGlobalObject = pObject;

    // Call virtual function at vtable offset 8 (third entry)
    // Typical use: release, init, or custom behavior in EA EARS engine objects
    void (*vfunc)(void*) = reinterpret_cast<void (*)(void*)>((*(int**)pObject)[2]);
    vfunc(pObject);

    // Call secondary function – often a destructor, factory cleanup, or size-dependent operation
    FUN_004df980(arg2);
}