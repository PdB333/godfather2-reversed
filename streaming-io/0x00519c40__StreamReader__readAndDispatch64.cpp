// FUNC_NAME: StreamReader::readAndDispatch64
void StreamReader::readAndDispatch64(void* thisPtr, void** callbackTable) {
    // thisPtr + 0x18 holds a pointer to a buffer of 64-bit values
    uint64_t* bufferPtr = (uint64_t*)((*(int*)((char*)thisPtr + 0x18) + 3) & 0xFFFFFFFC);
    *(uint64_t**)((char*)thisPtr + 0x18) = bufferPtr; // update stored pointer (redundant but ensures alignment)
    uint64_t value = *bufferPtr;
    *(uint64_t**)((char*)thisPtr + 0x18) = bufferPtr + 1; // advance past read value
    uint32_t low = (uint32_t)value;
    uint32_t high = (uint32_t)(value >> 32);
    // Call the function pointer from the callback table with the two halves
    ((void (*)(uint32_t, uint32_t))(*callbackTable))(low, high);
}