// FUNC_NAME: InterfaceResolver::resolveInterface
void InterfaceResolver::resolveInterface(uint32_t* outPtr)
{
    // +0x100: pointer to interface table (or vtable for interface queries)
    void** interfaceTable = *(void***)((int)this + 0x100);
    
    // Interface identifier hash (e.g., "IRenderable" / 0x369ac561)
    const uint32_t interfaceId = 0x369ac561;
    
    // Local output variable (initially null, will be set by the query)
    uint32_t* tempOut = nullptr; // corresponds to reused param_1 in decompiled code
    
    // Query the interface via the vtable at offset 0x10 (likely a virtual function)
    // The function signature: bool (*)(uint32_t id, void** outPtr)
    bool success = ((bool(*)(uint32_t, uint32_t**))(*interfaceTable)[4])(interfaceId, &tempOut);
    // Note: vtable offset 0x10 corresponds to index 4 (since pointers are 4 bytes)
    
    // Regardless of success, store the interface ID as the output value (might be a token/error code)
    *outPtr = interfaceId;
    return;
}