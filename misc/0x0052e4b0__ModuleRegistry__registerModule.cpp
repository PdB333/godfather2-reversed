// FUNC_NAME: ModuleRegistry::registerModule
void ModuleRegistry::registerModule(void)
{
    // Call virtual function at offset 4: likely returns a string or size.
    void* result = (*(void* (*)(void))(*gModuleDescriptor + 4))();  // +0x4: e.g., getModuleName()
    
    // Convert to hash ID (likely a CRC or FNV hash)
    gModuleNameId = FUN_0060d740(result);  // Store at +0x8 in module descriptor
    
    // Call virtual function at offset 0x10: e.g., onRegister() or init()
    (*(void (*)(void))(*gModuleDescriptor + 0x10))();
    
    // Link new module into global linked list (singly linked)
    gModuleNext = gModuleHead;        // +0x4: link to previous head
    gModuleHead = &gModuleDescriptor; // +0x0: head now points to new moduleDescriptor
    
    // Assign unique ID
    gModuleIdCounter++;
    gModuleId = gModuleIdCounter;     // +0xC: store ID in module descriptor
    
    // Finalize registration (maybe calls module's virtual function)
    FUN_0052e5f0();
}