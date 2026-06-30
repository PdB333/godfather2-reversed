// FUNC_NAME: readTLSByte
// Reads a byte from a per-thread data structure indexed by EAX and an offset pointer.
// The base address is obtained from the thread-local storage (TLS) array at FS:[0x2c].
// The byte is located at: base + index * 0x50 + 0x55 + *offsetPtr
// This is likely a helper to access a 2D byte table stored in TLS.

char __fastcall readTLSByte(int index, int* offsetPtr) {
    // index is passed in EAX (implicit first parameter)
    // offsetPtr is the explicit parameter (param_1)
    
    // Get the TLS array pointer from the Thread Environment Block (TEB)
    // FS:[0x2c] points to the TLS array (array of pointers)
    int* tlsArray = *(int**)(__readfsdword(0x2c)); // __readfsdword is compiler intrinsic for FS segment
    
    // Dereference the first TLS slot (index 0) to get a base pointer
    int base = *(int*)(tlsArray + 2); // +8 bytes from start of TLS slot? Actually tlsArray[0] is a pointer, then add 8 to that pointer? Wait: expression is *(int *)(**(int **)(FS+0x2c) + 8). So we take the value at FS+0x2c (which is a pointer to a pointer), dereference it to get a pointer (the first TLS slot), then add 8 to that pointer, then dereference as int. So base = *(int*)(tlsArray[0] + 8);
    // But careful: tlsArray is an array of pointers (void*). tlsArray[0] is the first pointer. Then add 8 to that pointer and read an int.
    // So base = *(int*)(tlsArray[0] + 8);
    
    // Compute final address
    char* address = (char*)(base + index * 0x50 + 0x55 + *offsetPtr);
    
    return *address;
}