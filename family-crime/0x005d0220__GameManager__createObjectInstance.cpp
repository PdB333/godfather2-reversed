// FUNC_NAME: GameManager::createObjectInstance
undefined4* GameManager::createObjectInstance(void) {
    uint flags = *(uint*)(this + 0x60); // +0x60: Object flags/mode
    
    if ((flags & 0x80000) != 0) {
        // Two-object mode (e.g., co-op or split-screen)
        undefined4* newBlock = (undefined4*)allocMemory(0x124, 0);
        if (newBlock == (undefined4*)0x0) {
            return (undefined4*)0x0;
        }
        
        undefined4* result = newBlock + 1; // Skip header
        *newBlock = 2; // Store count or type
        // Construct two objects of size 0x90 using constructObject as constructor
        _vector_constructor_iterator_(result, 0x90, 2, constructObject);
        
        // Update flags: clear bits that were set, set bits 0x4200
        *(uint*)(this + 0x60) = (flags & 0x70c1e) | 0x4200;
        initializeObject(this);
        *(uint*)(this + 0x60) = flags | 0x100000;
        initializeObject(this);
        
        return result;
    }
    
    // Single-object mode
    int newObj = allocMemory(0x90, 0);
    if (newObj != 0) {
        undefined4* result = constructObject();
        initializeObject(this);
        return result;
    }
    
    initializeObject(this);
    return (undefined4*)0x0;
}