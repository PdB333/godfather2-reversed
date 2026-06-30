// FUNC_NAME: getComponentFromEntity
// Address: 0x006a5470
// Retrieves a component pointer from an entity via a 3-level offset chain and validates it.
// Offsets: entity +0x4 -> +0xc -> +0x2c gives the component pointer.
// The validation function at 0x0088d5f0 returns 0 if the pointer is invalid, then sets output to null.
void* __cdecl getComponentFromEntity(void* output, int entityPtr) {
    void** outPtr = (void**)output;
    // Dereference: entity->field_0x4 (likely pointer to component container)
    // Then container->field_0xc (likely array or list of components)
    // Then field_0x2c (specific component pointer)
    void* component = *(void**)(*(int*)(*(int*)(entityPtr + 4) + 0xc) + 0x2c);
    *outPtr = component;
    // Validate retrieved component
    if (FUN_0088d5f0((int)output) == 0) {
        *outPtr = 0;
    }
    return output;
}