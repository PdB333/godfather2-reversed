// FUNC_NAME: RefCounted::addRef
void __thiscall RefCounted::addRef(RefCounted* thisObject, void* resource) {
    // Set the "outstanding reference" flag on the resource (offset +0x1b94)
    *(uint32_t*)((uint8_t*)resource + 0x1b94) |= 0x80000000;

    // If the current reference count is zero, perform initial setup on the resource
    if (*(int32_t*)((uint8_t*)thisObject + 0xec) == 0) {
        FUN_008c1730(0, resource); // likely initializes or locks resource
    }

    // Increment reference count
    (*(int32_t*)((uint8_t*)thisObject + 0xec))++;

    // After increment, if count > 1, trigger an additional action (possibly error recovery)
    if (*(uint32_t*)((uint8_t*)thisObject + 0xec) > 1) {
        FUN_008c1730(0, 0); // likely cleanup or unlock with null resource
    }
}