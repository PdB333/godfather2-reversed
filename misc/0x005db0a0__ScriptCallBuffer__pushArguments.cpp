// FUNC_NAME: ScriptCallBuffer::pushArguments
void __thiscall ScriptCallBuffer::pushArguments(int *thisPtr, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    // thisPtr points to a structure; dereference to get the base address of the data block.
    int *basePtr = *thisPtr;  // +0x00: pointer to internal data block (possibly vtable or mData)
    
    // +0x14: pointer to current write position within the data block (mWriteHead)
    int **writeHeadField = (int **)(basePtr + 0x14);  // address of the field holding the write pointer
    int *writeHead = *writeHeadField;
    
    // Write address of a global callback/function pointer (PTR_LAB_011273e0)
    *writeHead = (int)&PTR_LAB_011273e0;
    writeHead++;  // advance by 4 bytes
    
    // Write the first four arguments (arg2, arg3, arg4, arg5) directly
    *writeHead = arg2;
    writeHead++;
    *writeHead = arg3;
    writeHead++;
    *writeHead = arg4;
    writeHead++;
    
    // Align writeHead to a 4-byte boundary (required for arg5 maybe due to float/double alignment)
    writeHead = (int *)(((int)writeHead + 3) & ~3);
    
    *writeHead = arg5;
    writeHead++;
    *writeHead = arg6;
    writeHead++;
    
    // Update the stored write pointer
    *writeHeadField = writeHead;
}