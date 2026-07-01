// FUNC_NAME: EARS::Framework::TemporaryObjectManager::processTemporaryObject
void __cdecl processTemporaryObject(void)
{
    int *tempObj; // pointer to allocated temporary object
    int *refCountPtr;

    // Allocate a 100-byte temporary object (likely a small manager or action object)
    tempObj = (int *)operator new(100);
    if (tempObj == (int *)0x0) {
        tempObj = (int *)0x0;
    }
    else {
        // Initialize reference counting with 2 references (one for the caller, one for the object)
        RefCountedObject::initRefCount(2, 1);
        // Set vtable pointer (first entry) from a known global vtable
        *tempObj = (int)&PTR_LAB_00d7519c; // +0: vtable
        // Set secondary vtable or function table at offset 24 (6 ints from start)
        tempObj[6] = (int)&PTR_FUN_00d7518c; // +0x18: secondary pointer
        // Store a callback function pointer at offset 28
        tempObj[7] = (int)FUN_00855af0; // +0x1C: callback
        tempObj[8] = 0;  // +0x20: some field
        tempObj[9] = 0;  // +0x24: some field
        tempObj[10] = 0; // +0x28: some field
        // Additional initialization (parameter 0)
        setupAction(0);
        // Set a self-reference pointer at offset 20 (5 ints from start) to point to the secondary pointer
        tempObj[5] = (int)(tempObj + 6);
        // Increment reference count at offset 8 (2 ints from start)
        tempObj[2] = tempObj[2] + 1;
    }

    // Use a local variable as a temporary registration/payload (stack offset 4)
    int localReg; // uninitialized stack variable
    registerAction(&localReg);

    // Perform processing on all such objects
    processActions();

    // Release reference to the temporary object (decrement ref count)
    if (tempObj != (int *)0x0) {
        refCountPtr = tempObj + 2;
        *refCountPtr = *refCountPtr - 1;
        if (*refCountPtr == 0) {
            // Call virtual destructor via vtable (at offset 8 from vtable pointer)
            (*(void (__thiscall **)(int *))(*tempObj + 8))(tempObj);
        }
    }

    // Cleanup any global state
    cleanupActions();
}