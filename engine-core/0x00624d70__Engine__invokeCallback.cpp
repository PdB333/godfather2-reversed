// FUNC_NAME: Engine::invokeCallback
void Engine::invokeCallback(void* thisPtr) {
    // Local output buffer (3 ints) initialized to 0
    int outBuffer[3] = {0, 0, 0};

    // DAT_012234ac points to a table of function pointer addresses.
    // Offset 4 (byte offset 4) holds a pointer to a thunk/function pointer.
    // Double indirection: read the pointer at table+4, then dereference it to get the actual function.
    void (*method)(void*, int*) = *(void (**)(void*, int*))(*((void***)((char*)DAT_012234ac + 4)));

    // Invoke the method with this and the output buffer
    method(thisPtr, outBuffer);
}