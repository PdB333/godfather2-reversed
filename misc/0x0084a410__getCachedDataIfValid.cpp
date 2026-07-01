// FUNC_NAME: getCachedDataIfValid
int* __fastcall getCachedDataIfValid(int* data) 
{
    // data[5] is a validity flag at offset 0x14
    // data[4] is a pointer to a buffer at offset 0x10
    // *data is a pointer to a vtable or descriptor, whose +0x4 contains a type/ID
    // The second int of the buffer (*(int*)(data[4]+4)) must equal the type/ID from the descriptor
    if ((data[5] == 1) && (((int*)data[4])[1] == *(int*)(*data + 4))) 
    {
        // Return the first int of the buffer (the actual cached data pointer)
        return *(int**)data[4];
    }
    return 0;
}