// FUNC_NAME: GlobalManager::processQuery
void GlobalManager::processQuery(void* objPtr) {
    // Temporary buffer (likely a Vector3 or struct with 3 floats)
    struct SQueryData { float x, y, z; };
    SQueryData data = {0.0f, 0.0f, 0.0f};

    // Call function pointer from global singleton at DAT_012234b8 + 0x28
    // +0x28 likely a vtable offset for a query method
    void (*func)(void*, SQueryData*) = 
        (void (*)(void*, SQueryData*))(*(int*)(*(int*)DAT_012234b8 + 0x28));
    func(objPtr, &data);
}