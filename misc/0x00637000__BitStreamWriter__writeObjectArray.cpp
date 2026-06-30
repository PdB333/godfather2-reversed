// FUNC_NAME: BitStreamWriter::writeObjectArray
void __thiscall BitStreamWriter::writeObjectArray(int thisPtr) {
    int count = *(int *)(thisPtr + 0x24);           // +0x24: number of objects in array
    int localCount = count;                          // preserve original count
    int loopEnd = count;

    // Write total count to stream
    (*(void (__stdcall *)(int, void*, int, int))funcTable[1])(funcTable[0], &localCount, 4, funcTable[2]);

    for (int i = 0; i < loopEnd; i++) {
        int* objPtr = *(int**)(thisPtr + 0x1c)[i];   // +0x1c: array of object pointers
        if (objPtr == nullptr || objPtr + 0x10 == nullptr) {
            // Object or its data pointer is invalid, write zero length
            int zero = 0;
            (*(void (__stdcall *)(int, void*, int, int))funcTable[1])(funcTable[0], &zero, 4, funcTable[2]);
        } else {
            int dataSize = *(int*)(objPtr + 0x0c) + 1; // +0x0c: size field (+1 for header?)
            (*(void (__stdcall *)(int, void*, int, int))funcTable[1])(funcTable[0], &dataSize, 4, funcTable[2]);
            (*(void (__stdcall *)(int, void*, int, int))funcTable[1])(funcTable[0], objPtr + 0x10, dataSize, funcTable[2]);
            loopEnd = count;  // restore count (unnecessary, but matches decompiled)
        }
    }
}