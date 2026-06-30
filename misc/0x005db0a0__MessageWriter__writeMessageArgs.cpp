// FUNC_NAME: MessageWriter::writeMessageArgs
void __thiscall MessageWriter::writeMessageArgs(undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6)
{
    // param_1 (this) points to an object containing a pointer to a buffer descriptor at offset 0x0.
    // The buffer descriptor has a write pointer at offset 0x14.
    int* bufferDesc = *(int**)this; // dereference this to get buffer descriptor address
    int** writePtrPtr = (int**)(bufferDesc + 0x14); // pointer to the write pointer field (+0x14)

    // Write a pointer to a global label (likely a message type identifier or vtable)
    **writePtrPtr = (int)&PTR_LAB_011273e0;
    (*writePtrPtr)++; // advance write pointer by 4 bytes

    // Write the next 4 parameters sequentially
    **writePtrPtr = param2;
    (*writePtrPtr)++;
    **writePtrPtr = param3;
    (*writePtrPtr)++;
    **writePtrPtr = param4;
    (*writePtrPtr)++;

    // Align write pointer to 4-byte boundary before writing param5
    *writePtrPtr = (int*)(((int)*writePtrPtr + 3) & 0xfffffffc);
    **writePtrPtr = param5;
    (*writePtrPtr)++;

    // Write param6
    **writePtrPtr = param6;
    (*writePtrPtr)++;
}