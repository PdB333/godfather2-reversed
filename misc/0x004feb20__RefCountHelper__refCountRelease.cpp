// FUNC_NAME: RefCountHelper::refCountRelease
undefined1 * __fastcall RefCountHelper::refCountRelease(void *unused_ecx, void *objPtr, int *refCountStruct) {
    int *refCounter;
    char canDelete;
    int localValidFlag = 0;

    if (refCountStruct != nullptr) {
        // Call the "canDelete" method at vtable offset 8, passing the object pointer
        canDelete = (**(char (__thiscall **)(void *))(*(int *)refCountStruct + 8))(objPtr);
        if (canDelete != '\0') {
            // Decrement reference count
            refCounter = refCountStruct + 1;
            *refCounter = *refCounter - 1;
            if (*refCounter == 0) {
                // If ref count reaches zero, call destructor at vtable offset 4
                (**(void (__thiscall **)(void))(*(int *)refCountStruct + 4))();
            }
            // Return pointer to a local variable (success indicator) – typically reinterpreted as boolean or pointer
            return (undefined1 *)&localValidFlag;
        }
        // Decrement reference count even if canDelete returns false
        refCounter = refCountStruct + 1;
        *refCounter = *refCounter - 1;
        if (*refCounter == 0) {
            (**(void (__thiscall **)(void))(*(int *)refCountStruct + 4))();
        }
    }
    return (undefined1 *)0x0;
}