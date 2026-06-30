// FUNC_NAME: BitStream::readAndCallFunction
void BitStream::readAndCallFunction(int param_1, void (**funcPtr)(int, int, int, int64_t)) {
    int arg0 = **(int**)(param_1 + 0x18);           // +0x18: stream buffer pointer (pointer to current read position)
    int* alignedPtr = (int*)((int)*(int**)(param_1 + 0x18) + 7U & 0xfffffffc); // align to next DWORD boundary
    *(int**)(param_1 + 0x18) = alignedPtr;          // update stream position to aligned pointer
    int arg1 = *alignedPtr;                         // read first DWORD
    *(int**)(param_1 + 0x18) = alignedPtr + 1;
    int arg2 = alignedPtr[1];                       // read second DWORD
    *(int**)(param_1 + 0x18) = alignedPtr + 2;
    int64_t arg3_4 = *(int64_t*)(alignedPtr + 2);   // read 8-byte value (e.g., double or int64)
    *(int**)(param_1 + 0x18) = alignedPtr + 4;      // advance past the 8 bytes
    (*(*funcPtr))(arg0, arg1, arg2, (int)arg3_4, (int)(arg3_4 >> 32)); // call function with 5 arguments
}