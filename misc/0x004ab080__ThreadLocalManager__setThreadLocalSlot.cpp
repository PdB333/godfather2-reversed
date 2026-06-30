// FUNC_NAME: ThreadLocalManager::setThreadLocalSlot
// Function address: 0x004ab080
// Role: Sets a value in a thread-local storage slot. Uses FS segment to access per-thread data.
// The offset at this+0x18 is an index into a per-thread array located at (baseAddr + 0x98).

void ThreadLocalManager::setThreadLocalSlot(undefined4 *valuePtr) {
    // Retrieve TLS pointer from FS segment (offset 0x2c)
    // This is typical for accessing thread-local storage on Windows x86.
    // The pointer at fs:0x2c points to a structure from which we derive a base address.
    int *tlsBasePtr = (int *)__readfsdword(0x2c);
    // Dereference to get an inner pointer, then add offset 8, dereference to get base integer
    int baseAddr = *(int *)(*(int **)tlsBasePtr + 8);
    // The index is stored at this+0x18
    int index = *(int *)((char *)this + 0x18);
    // Compute target address: baseAddr + 0x98 + index
    int *target = (int *)(baseAddr + 0x98 + index);
    // Write the value
    *target = *valuePtr;
}