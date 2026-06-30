// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, const char* configPath)
{
    int* vtablePtr;
    int dataCopy;
    int duplicateData;
    int* allocator;
    undefined4 local_c[3]; // 12 bytes stack buffer

    // Set vtable for GodfatherGameManager
    this->vtable = &GodfatherGameManager_vtable;

    // Clear local buffer
    local_c[0] = 0;
    local_c[1] = 0;
    local_c[2] = 0;

    // Get global allocator (e.g., heap manager) from DAT_012234ec + 4
    allocator = *(int**)(DAT_012234ec + 4);
    // Store this as the global singleton instance
    g_GodfatherGameManager = this;

    // Call allocator method (offset +8) – likely pre-allocation or reference bump
    (*(code**)(*allocator + 8))();

    // Duplicate or allocate data using the allocator: likely creates a deep copy of local_c
    dataCopy = FUN_004265d0(&local_c, allocator);
    int* tmpAllocator = allocator;

    // Call allocator method again (offset +8) – maybe release or finalize
    (*(code**)(*allocator + 8))(allocator);

    // If allocation succeeded, duplicate again (or extract internals)
    if (dataCopy != 0) {
        duplicateData = FUN_004265d0(dataCopy, tmpAllocator);
    } else {
        duplicateData = 0;
    }

    // Store the duplicated data into this object
    FUN_005d9fb0(tmpAllocator, duplicateData);

    // Initialize counters/pointers to zero
    this->field_3 = 0;
    this->field_4 = 0;
    this->field_5 = 0;

    // If the first copy succeeded, release the copy using allocator method at offset +4
    if (dataCopy != 0) {
        (*(code**)(*allocator + 4))(dataCopy, 0);
    }

    // Call allocator method at offset +0xC – possibly cleanup or reset
    (*(code**)(*allocator + 0xC))();

    // Load the config file or resource
    FUN_005d98b0(configPath);

    return this;
}