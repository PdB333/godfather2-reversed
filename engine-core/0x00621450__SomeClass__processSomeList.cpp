// FUNC_NAME: SomeClass::processSomeList
bool SomeClass::processSomeList(void)
{
    // unaff_EDI is likely the 'this' pointer
    // +0x10: pointer to some container/list
    // +0x04: pointer to vtable or another object
    int* containerPtr = *(int**)(this + 0x10);
    bool result = false;
    
    if (containerPtr != 0) {
        // Call helper function that fills local_20 and local_1c
        // local_20 seems to be a node pointer, local_1c an index or sub-node
        FUN_00621b20(&stack0x00000004);
        
        if (local_20 == 0) {
            FUN_00b97aea(); // likely an assertion or error handler
        }
        
        // +0x1c: size or count field in the container
        if (local_1c == *(int*)(local_20 + 0x1c)) {
            FUN_00b97aea(); // assertion/error
        }
        
        // Read 3 consecutive 8-byte values from local_1c + offsets
        // These might be packed data (e.g., two 32-bit values per 8-byte slot)
        __int64 val1 = *(__int64*)(local_1c + 0xc);
        __int64 val2 = *(__int64*)(local_1c + 0x14);
        __int64 val3 = *(__int64*)(local_1c + 0x1c);
        
        // Extract a 16-bit field from the high part of val3
        short field = (short)((unsigned long long)val3 >> 32);
        result = (field == 1);
        
        // Store val3 in local_8 (overwrites the field we just read)
        *(__int64*)&local_8 = val3;
        
        if (result) {
            // Extract high 32 bits of val1 and call a virtual function
            // vtable at *(this+4) + offset 4
            int highVal1 = (int)((unsigned long long)val1 >> 32);
            int* vtable = *(int**)(this + 4);
            (**(code**)(vtable + 1))(highVal1, 0); // virtual call with 2 params
        }
        
        // Get count from the container
        int containerCount = *(int*)(containerPtr + 0x1c);
        
        // Verify container pointer hasn't changed
        if (local_20 != containerPtr) {
            FUN_00b97aea(); // assertion/error
        }
        
        result = (local_1c != containerCount);
        if (result) {
            // Call function to advance to next element
            FUN_006217f0(*(int*)(this + 0x10), &local_20, local_20, local_1c);
        }
    }
    
    return result;
}