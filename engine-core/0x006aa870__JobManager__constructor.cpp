// FUNC_NAME: JobManager::constructor
unsigned int* __thiscall JobManager::constructor(unsigned int* thisPtr, int param_2) {
    // Base class initialization (likely EARS::Object or similar)
    FUN_0046c590(param_2);
    
    // Set up vtable pointers
    *thisPtr = &PTR_FUN_00d5d9dc;                     // +0x00: primary vtable
    thisPtr[0x0F] = &PTR_LAB_00d5d9cc;                // +0x3C: secondary vtable
    thisPtr[0x12] = &PTR_LAB_00d5d9c8;                // +0x48: tertiary vtable
    
    // Zero out fields at specific offsets
    thisPtr[0x14] = 0;                                 // +0x50
    thisPtr[0x15] = 0;                                 // +0x54
    *(uint16_t*)(thisPtr + 0x16) = 0;                 // +0x58
    *(uint16_t*)((uint8_t*)thisPtr + 0x5A) = 0;       // +0x5A
    thisPtr[0x17] = 0;                                 // +0x5C
    *(uint16_t*)(thisPtr + 0x18) = 0;                 // +0x60
    *(uint16_t*)((uint8_t*)thisPtr + 0x62) = 0;       // +0x62
    
    // Another static init call
    FUN_006aa6f0();
    
    // Clear a byte at +0xF2
    *(uint8_t*)((uint8_t*)thisPtr + 0xF2) = 0;
    
    // Initialize up to 8 job slots
    for (int i = 0; i < 8; i++) {
        // Temporary job structure on stack
        Job job;
        job.vtable = &PTR_FUN_00d5d9b0;               // job's vtable
        job.field_04 = 0;                             // +0x04
        job.field_08 = 0;                             // +0x08
        job.field_0C = 0;                             // +0x0C
        job.destructor1 = nullptr;                    // +0x10
        job.field_14 = 0;                             // +0x14
        job.field_18 = 0;                             // +0x18
        job.field_1C = 0;                             // +0x1C
        job.destructor2 = nullptr;                    // +0x20
        job.field_24 = 0;                             // +0x24
        job.field_28 = 0;                             // +0x28
        job.field_2C = 0;                             // +0x2C
        job.destructor3 = nullptr;                    // +0x30
        job.field_34 = 0;                             // +0x34
        job.field_38 = 0;                             // +0x38
        job.field_3C = 0;                             // +0x3C
        job.destructor4 = nullptr;                    // +0x40
        job.field_44 = 0;                             // +0x44
        job.field_48 = 0;                             // +0x48
        job.field_4C = 0;                             // +0x4C
        job.field_50 = 0;                             // +0x50
        job.field_54 = 0;                             // +0x54
        job.field_58 = 0;                             // +0x58
        job.field_5C = 0;                             // +0x5C
        job.field_60 = 0;                             // +0x60
        job.field_64 = 0;                             // +0x64
        job.priority = 100;                           // +0x68
        job.field_6C = 0;                             // +0x6C
        
        // If there is still room in the job array, record the new job
        if (thisPtr[0xF1] < 8) {                      // +0x3C4: job count
            thisPtr[0xF1]++;
            FUN_006a9fe0(&job);                       // Add job to internal list
        }
        
        // Clean up any dynamically allocated sub-objects within the temp job
        if (job.field_34 != 0) {
            ((void (*)(void*))job.destructor2)((void*)job.field_34);
        }
        if (job.field_44 != 0) {
            ((void (*)(void*))job.destructor3)((void*)job.field_44);
        }
        if (job.field_54 != 0) {
            ((void (*)(void*))job.destructor4)((void*)job.field_54);
        }
        if (job.field_64 != 0) {
            ((void (*)(void*))job.destructor1)((void*)job.field_64);
        }
    }
    
    return thisPtr;
}