// FUNC_NAME: DataStream::writeTypedArgs
void __thiscall DataStream::writeTypedArgs(void* thisPtr, int param2, int param3)
{
    // Dereference this to get the write context pointer (first field of the stream object)
    int* context = *(int**)thisPtr;

    // Write a pointer to type info (global type descriptor) at current position
    *(void**)(context[0x14]) = &PTR_LAB_01126130; // gs_typeInfo

    // Advance the write pointer by 4 bytes (size of a pointer)
    context[0x14] += 4;

    // Align to 4-byte boundary and write param2
    int aligned = (context[0x14] + 3U) & 0xFFFFFFFC;
    *(int*)aligned = param2;
    context[0x14] = aligned + 4; // advance past written value

    // Align again and write param3
    aligned = (context[0x14] + 3U) & 0xFFFFFFFC;
    *(int*)aligned = param3;
    context[0x14] = aligned + 4;
}