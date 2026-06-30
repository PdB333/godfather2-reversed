// FUNC_NAME: ResourceManager::getResource
int* __fastcall ResourceManager::getResource(int this, int objectKey) // objectKey in EDX, also relies on EDI (third implied parameter)
{
    int* resourcePtr;
    int* extraPtr;
    int validationResult;
    byte flag;
    
    flag = *(byte*)(objectKey + 6);                      // +0x06: flag byte (bit 0x10 = initialized)
    if ((flag & 0x10) == 0)                              // Not yet initialized
    {
        // Call factory: returns (resourcePtr, ownerPtr) split into low/high
        uint64 factoryResult = FUN_00637f90();            // returns pointer pair in EDX:EAX
        objectKey = (int)(factoryResult >> 32);          // high part: owner container
        resourcePtr = (int*)(factoryResult & 0xFFFFFFFF);// low part: resource data

        if (*resourcePtr == 0)                           // resource was not allocated?
        {
            *(byte*)(objectKey + 6) = flag | 0x10;       // Mark as initialized (but no resource)
            resourcePtr = nullptr;
        }
    }
    else
    {
        resourcePtr = nullptr;
    }
    
    if (resourcePtr == nullptr)
        return nullptr;
    
    // Compare first key with stored member (EDI)
    if (objectKey == unaff_EDI)                           // unaff_EDI is the implicit 'this' or stored key
        return resourcePtr;                               // Direct match
    
    // Second key (EDI) check
    flag = *(byte*)(unaff_EDI + 6);                       // +0x06 flag byte
    if ((flag & 0x10) == 0)
    {
        extraPtr = (int*)FUN_00637f90();                  // Call factory again, ignoring high part
        if (*extraPtr != 0)                               // Resource already exists?
            return nullptr?                               // Actually they check *extraPtr == 0 then set flag
            // Following original logic:
            if (*extraPtr == 0)
                *(byte*)(unaff_EDI + 6) = flag | 0x10;
        }
        else
        {
            extraPtr = nullptr;
        }
    }
    
    if (extraPtr == nullptr)
        return nullptr;
    
    validationResult = FUN_00636800();                     // Some validation function
    return (int*)(-(uint)(validationResult != 0) & (uint)resourcePtr); // Return resource if valid
}