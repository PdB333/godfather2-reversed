// FUNC_NAME: ReadTypeInfoFromStream
bool ReadTypeInfoFromStream(void* param_1) {
    undefined4* bufferPtr; // derived from param_1+8
    int typeId;
    int floatValue;
    undefined4 result;
    int* typeInfo;
    undefined4* source;

    // Initial buffer pointer
    bufferPtr = *(undefined4**)((unsigned char*)param_1 + 8);
    
    // Check if type tag is 6 (sentinel)
    if ((bufferPtr[-2] == 6) && (*(char*)(bufferPtr[-1] + 6) == '\0')) {
        // Use a different source: offset 0x10 from the previous entry's value
        source = (undefined4*)(bufferPtr[-1] + 0x10);
    } else {
        // Default source: param_1 + 0x40
        source = (undefined4*)((unsigned char*)param_1 + 0x40);
    }
    
    // Copy 8 bytes from source into buffer
    *bufferPtr = *source;
    bufferPtr[1] = source[1];
    // Advance buffer by 8 bytes
    *(unsigned int*)((unsigned char*)param_1 + 8) += 8;
    
    // Check a condition on a secondary buffer at param_1+0x10
    if (*(unsigned int*)(*(int*)((unsigned char*)param_1 + 0x10) + 0x20) <= 
        *(unsigned int*)(*(int*)((unsigned char*)param_1 + 0x10) + 0x24)) {
        // Call error handler
        FUN_00627360();
    }
    
    // Re-read the updated buffer pointer
    bufferPtr = *(undefined4**)((unsigned char*)param_1 + 8);
    // Write type tag 4 (float constant?)
    *bufferPtr = 4;
    // Look up string "__fenv" with length 6, store result
    result = FUN_00638920(param_1, "__fenv", 6);
    bufferPtr[1] = result;
    // Advance buffer
    *(unsigned int*)((unsigned char*)param_1 + 8) += 8;
    
    // Now go back to the previous 8 bytes (the tag and value just written?)
    typeId = *(int*)(*(unsigned int*)((unsigned char*)param_1 + 8) - 8);
    floatValue = *(int*)(*(unsigned int*)((unsigned char*)param_1 + 8) - 4);
    
    // Based on type ID, get corresponding type info from a factory
    if (typeId == 3) {
        // Check if the value is actually a float
        if ((float)floatValue == *(float*)&floatValue) {
            typeInfo = (int*)FUN_00637f10();
            goto LAB_0062dd28;
        }
    } else if (typeId == 4) {
        typeInfo = (int*)FUN_00637f90();
        goto LAB_0062dd28;
    }
    // Default fallback
    typeInfo = (int*)FUN_00637ea0();
    
LAB_0062dd28:
    // Overwrite the type tag and value with the type info (two ints)
    *(int*)(*(unsigned int*)((unsigned char*)param_1 + 8) - 8) = *typeInfo;
    *(int*)(*(unsigned int*)((unsigned char*)param_1 + 8) - 4) = typeInfo[1];
    
    // Check if the overwritten location is null, and return non-zero if first word not 0
    typeInfo = (int*)(*(unsigned int*)((unsigned char*)param_1 + 8) - 8);
    if (typeInfo == (int*)0x0) {
        return true;
    }
    return *typeInfo != 0;
}