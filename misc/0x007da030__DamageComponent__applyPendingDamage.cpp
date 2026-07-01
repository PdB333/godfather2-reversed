// FUNC_NAME: DamageComponent::applyPendingDamage

void __fastcall DamageComponent::applyPendingDamage(int thisPtr) {
    // thisPtr: pointer to DamageComponent instance
    // Offsets: +0x58 = m_pOwner (pointer to a large character/entity object)
    //          +0x98 = m_damageState (0 = normal, 0x48 = special state)
    // The owner object has four hit-source queues at offsets 0x2bc4, 0x2bc8, 0x2bcc, 0x2bd0
    
    uint ownerPtr = *(uint*)(thisPtr + 0x58);
    int damageState = *(int*)(thisPtr + 0x98);
    
    // If damage state is not 0 or 0x48, bail out (already processing or invalid)
    if (damageState != 0 && damageState != 0x48) {
        return;
    }
    
    // Check if all four hit-source queues are empty
    bool allQueuesEmpty = (*(int*)(ownerPtr + 0x2bc4) == 0) &&
                          (*(int*)(ownerPtr + 0x2bc8) == 0) &&
                          (*(int*)(ownerPtr + 0x2bcc) == 0) &&
                          (*(int*)(ownerPtr + 0x2bd0) == 0);
    
    void* hitData; // Will hold pointer to a HitData object (0xF4 bytes)
    
    if (allQueuesEmpty) {
        // No pending hits: allocate a new HitData object
        struct AllocationParams {
            int param1; // =2
            int param2; // =0x10
            int param3; // =0
        };
        AllocationParams allocParams;
        allocParams.param1 = 2;
        allocParams.param2 = 0x10;
        allocParams.param3 = 0;
        
        hitData = (void*)FUN_009c8ed0(0xF4, &allocParams); // Memory allocator
        
        if (hitData != nullptr) {
            FUN_006d6ae0(); // Constructor for HitData base? (sets vtable)
            // Set vtable pointers (virtual method tables)
            *(uint*)hitData = (uint)&PTR_FUN_00d588f0;        // Main vtable
            *(uint*)((uint)hitData + 0x3C) = (uint)&PTR_LAB_00d588e0; // offset 0x3C
            *(uint*)((uint)hitData + 0x48) = (uint)&PTR_LAB_00d588dc; // offset 0x48
            *(uint*)((uint)hitData + 0x50) = (uint)&PTR_LAB_00d588d8; // offset 0x50
        }
        
        // Apply the hit data (empty/default)
        FUN_007d98a0(hitData);
    } else {
        // There are pending hits: get the first one from the queue (offset 0x2bc4)
        void* existingHit = FUN_00446130((int*)(ownerPtr + 0x2bc4), 0); // Get from list
        FUN_007d98a0(existingHit);
    }
    
    // After hit data is applied, do further processing
    FUN_006d69c0(); // Probably destructor/unlock?
    
    int processedDamageState = *(int*)(thisPtr + 0x98);
    if (processedDamageState == 0) {
        processedDamageState = 0;
    } else {
        processedDamageState = processedDamageState - 0x48; // Convert state index
    }
    
    // Save/restore some context (maybe local buffer)
    FUN_006bfa70(processedDamageState + 0x68);
    
    // Read and store two values into global memory (likely a global context object)
    int globalContext = DAT_01129944;
    *(undefined8*)(globalContext + 0x108) = local_10; // saved from previous operations?
    *(undefined4*)(globalContext + 0x110) = local_8;
    
    // Update the owner's damage queue processing state
    uint newOwnerState = ownerPtr;
    if (allQueuesEmpty) {
        newOwnerState = (ownerPtr & 0xFFFFFF00) | 1; // Set low byte to 1
        if (*(int*)(ownerPtr + 0x2bd0) == 0) {
            goto LAB_007da15a;
        }
    }
    newOwnerState = newOwnerState & 0xFFFFFF00;
    
LAB_007da15a:
    FUN_006d76c0(ownerPtr, newOwnerState, 0); // Update owner state
    
    // Apply actual damage to the owner via a rendering/effect function
    FUN_006bfa70(local_8c); // Some buffer
    
    int finalDamageState = *(int*)(thisPtr + 0x98);
    if (finalDamageState == 0) {
        finalDamageState = 0;
    } else {
        finalDamageState = finalDamageState - 0x48;
    }
    FUN_00424dc0(*(undefined4*)(&DAT_00002494 + ownerPtr), finalDamageState, 0, 0, 0); // Apply damage effect
    
    // Clean up temporary local arrays
    if (local_5c[0] != 0) {
        FUN_004daf90(local_5c);
    }
    if (local_64[0] != 0) {
        FUN_004daf90(local_64);
    }
    
    return;
}