// FUNC_NAME: StreamManager::releaseStreamHandles
void __thiscall StreamManager::releaseStreamHandles(int thisPtr) {
    // Get the stream interface pointer at offset 0x28
    int* streamInterface = *(int**)(thisPtr + 0x28);
    // Second virtual function (offset 4) releases a stream handle pair
    typedef void (*ReleaseFunc)(int, int);
    ReleaseFunc releaseFunc = (ReleaseFunc)(*(int*)((int)streamInterface + 4));
    
    // Release first stream handle pair (offset 0x20a0, 0x20a4)
    releaseFunc(*(int*)(thisPtr + 0x20a0), *(int*)(thisPtr + 0x20a4));
    *(int*)(thisPtr + 0x20a0) = 0;
    *(int*)(thisPtr + 0x20a4) = 0;
    
    // Release second stream handle pair (offset 0x20a8, 0x20ac)
    releaseFunc(*(int*)(thisPtr + 0x20a8), *(int*)(thisPtr + 0x20ac));
    *(int*)(thisPtr + 0x20a8) = 0;
    *(int*)(thisPtr + 0x20ac) = 0;
}