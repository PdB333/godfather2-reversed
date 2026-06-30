// FUNC_NAME: SomeManager::initializeManager
void SomeManager::initializeManager(bool shouldAllocateSubData)
{
    // Allocate aligned block of 0xA20 bytes for manager data
    ManagerData* managerData = (ManagerData*)alignedMalloc(0xA20, 0x10);
    if (managerData != nullptr)
    {
        // Base initialization (zero memory, set vtable)
        baseInitialize();
        managerData->vtable = &ManagerData::vtable;  // +0x0
        managerData->field_0x286 = 0;                // +0x286*4 = +0xA18
        managerData->field_0x287 = 0;                // +0x287*4 = +0xA1C

        if (shouldAllocateSubData)
        {
            // Allocate sub-data of size 0x48
            SubData* subData = (SubData*)memoryAlloc(0x48);
            if (subData != nullptr)
            {
                uint32_t zeroStack[3] = {0, 0, 0};
                uint32_t handle = createResource(zeroStack);  // FUN_004b4d10
                managerData->field_0x287 = handle;
                // Store manager data pointer at offset 0x1C in this object
                *(ManagerData**)(this + 0x1C) = managerData;
                finalizeInit();  // FUN_0053fb10
                return;
            }
            managerData->field_0x287 = 0;
            *(ManagerData**)(this + 0x1C) = managerData;
            finalizeInit();
            return;
        }
    }
    // In case of failure, store (possibly null) manager data
    *(ManagerData**)(this + 0x1C) = managerData;
    finalizeInit();
}