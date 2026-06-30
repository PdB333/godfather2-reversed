// FUNC_NAME: BNKStreamManager::allocateStream
undefined4 __thiscall BNKStreamManager::allocateStream(BNKStreamManager* this, StreamContainer* container)
{
    int allocatedObj;
    int* interfacePtr;
    bool allocFailed;
    int local_18; // handle or result from constructor
    undefined4 local_14; // constructor arguments (stack struct)
    undefined4 local_10;
    undefined4 local_c;

    // Store pointer to this (the BNKStreamManager) into container's owner/manager slot
    container->manager = this; // container +0x14

    // AddRef on the manager (virtual call at vtable offset 8)
    (this->vtable->addRef)();

    // Allocate memory for the stream object (size 0x24 = 36 bytes)
    allocatedObj = operatorNew(0x24);
    allocFailed = (allocatedObj == 0);
    if (allocFailed) {
        interfacePtr = nullptr;
        allocatedObj = 0;
    }
    else {
        // Retrieve the manager pointer again (could be same as this)
        interfacePtr = container->manager; // container +0x14

        // Initialize a local struct to zeros (constructor args)
        local_14 = 0;
        local_10 = 0;
        local_c = 0;

        // AddRef on the interface again (likely a reference counter)
        (interfacePtr->vtable->addRef)();

        // Call a constructor that takes the local struct and interface
        // Returns a handle or object ID stored in local_18
        local_18 = FUN_004265d0(&local_14, interfacePtr);

        // Post-construction initialization (e.g., register in manager)
        FUN_004ca180();
    }

    // Store the allocated object pointer in container
    container->streamObject = allocatedObj; // container +0x10

    if (!allocFailed) {
        // If construction succeeded, release the temporary handle if non-zero
        if (local_18 != 0) {
            // Release the handle (virtual call at vtable offset 4)
            (interfacePtr->vtable->release)(local_18, 0);
        }
        // Destroy the local interface reference (virtual call at vtable offset 12)
        (interfacePtr->vtable->destroy)();
    }

    return 1; // Return success
}