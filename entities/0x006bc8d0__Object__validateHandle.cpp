// FUNC_NAME: Object::validateHandle
uint32_t Object::validateHandle(int32_t* thisPtr, uint32_t handle)
{
    int32_t outParam = 0;
    // Call virtual method at vtable offset 0x10 (likely isObjectValid or getObjectStatus)
    // Returns non-zero if valid
    char isValid = (*(char (**)(uint32_t, int32_t*))(*(uint32_t*)thisPtr + 0x10))(handle, &outParam);
    // If valid, return the handle; otherwise 0
    return (isValid != 0) ? handle : 0;
}