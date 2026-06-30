// FUNC_NAME: ResourceComponent::setHandle
// Function address: 0x006ca8e0
// Sets the resource handle at offset +0x6c using a lookup function and validates it.
void __thiscall ResourceComponent::setHandle(ResourceComponent* this, uint32_t param_2)
{
    uint32_t handle;

    // Lookup resource handle from given parameter (e.g., name ID or path hash)
    handle = FUN_006c9da0(param_2);
    *(uint32_t*)((int)this + 0x6c) = handle;  // +0x6c: resourceHandle

    if (handle != 0xffffffff) {
        // Validate the resource (e.g., check if loaded or exists)
        char isValid = FUN_0040fa60(handle & 0xff);
        if (isValid == '\0') {
            // Resource invalid, reset handle to sentinel
            *(uint32_t*)((int)this + 0x6c) = 0xffffffff;
        }
    }
    return;
}