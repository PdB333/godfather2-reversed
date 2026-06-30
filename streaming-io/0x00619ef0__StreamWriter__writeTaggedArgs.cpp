// FUNC_NAME: StreamWriter::writeTaggedArgs
void __thiscall StreamWriter::writeTaggedArgs(int* thisPtr, uint32_t value1, uint32_t value2, uint32_t value3)
{
    // Dereference this to get the internal buffer state structure
    int* bufferState = reinterpret_cast<int*>(*thisPtr);
    
    // Write a type descriptor / vtable pointer from a global table
    *reinterpret_cast<uint32_t*>(*(int*)(bufferState + 0x14)) = reinterpret_cast<uint32_t>(&PTR_LAB_011278a4);
    *(int*)(bufferState + 0x14) += 4; // Advance write pointer
    
    // Write first argument
    *reinterpret_cast<uint32_t*>(*(int*)(bufferState + 0x14)) = value1;
    *(int*)(bufferState + 0x14) += 4;
    
    // Write second argument
    *reinterpret_cast<uint32_t*>(*(int*)(bufferState + 0x14)) = value2;
    *(int*)(bufferState + 0x14) += 4;
    
    // Align write pointer to 4-byte boundary for the third argument
    uint32_t alignedPtr = (*(int*)(bufferState + 0x14) + 7) & ~3;
    *(int*)(bufferState + 0x14) = alignedPtr;
    
    // Write third argument at aligned position
    *reinterpret_cast<uint32_t*>(*(int*)(bufferState + 0x14)) = value3;
    *(int*)(bufferState + 0x14) += 4;
}