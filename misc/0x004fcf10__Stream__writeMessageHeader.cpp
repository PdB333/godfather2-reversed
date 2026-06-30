// FUNC_NAME: Stream::writeMessageHeader
void __thiscall Stream::writeMessageHeader(uint param_2, uint param_3, uint param_4, uint param_5, uint param_6, uint param_7)
{
    // param_1 = this (pointer to Stream)
    // mBuffer points to a Buffer structure (offset +0x00)
    // Buffer::writePos is at offset +0x14
    int* pBuffer = *(int**)this;             // Dereference this to get Buffer pointer
    int* writePtr = (int*)(pBuffer + 0x14);  // Buffer::writePos pointer (actually pointer to the pointer)

    // Write a function pointer (vtable or handler) at current write position
    **(int***)(writePtr) = &PTR_FUN_01124ea4; // store address of function pointer
    *writePtr = *writePtr + 4;                 // advance by 4 (no alignment needed yet)

    // Write param_2 with 4-byte alignment
    int* current = *(int**)writePtr;            // current write position
    current = (int*)((int)current + 7U & 0xfffffffc); // align to 4 bytes (round up to multiple of 4)
    *(int**)writePtr = current;                 // update write pointer
    *current = param_2;

    // Write param_3 with alignment
    current = *(int**)writePtr;
    current = (int*)((int)current + 7U & 0xfffffffc);
    *(int**)writePtr = current;
    *current = param_3;

    // Write param_4 with alignment
    current = *(int**)writePtr;
    current = (int*)((int)current + 7U & 0xfffffffc);
    *(int**)writePtr = current;
    *current = param_4;

    // Write 64-bit value (param_6, param_7) with 4-byte alignment (treat as two 32-bit words)
    current = *(int**)writePtr;
    current = (int*)((int)current + 7U & 0xfffffffc);
    *(int**)writePtr = current;
    *(int64_t*)current = CONCAT44(param_7, param_6); // combine into 64-bit
    *(int**)writePtr = *(int**)writePtr + 8;            // advance by 8 bytes

    // Write param_5 with no extra alignment (assumes already aligned)
    current = *(int**)writePtr;
    *(int**)writePtr = current + 1;                     // advance by 4
    *current = param_5;
}