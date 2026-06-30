// FUNC_NAME: setThreadLocalParam

void setThreadLocalParam(int value) {
    // 0x00483a40 - Writes a value to a fixed thread-local storage location (likely engine TLS).
    // Derives target from FS segment: FS:[0x2c] holds a pointer to some thread-local data structure,
    // then offset 0x34 within that structure receives the parameter.
    // Equivalent x86: mov eax, fs:[0x2c]; mov ecx, [eax]; add ecx, 0x34; mov [ecx], param_1
    uint32_t tlsBase = __readfsdword(0x2c);                 // Get pointer from TLS slot 0x2c
    uint32_t* tlsPtr = *(uint32_t**)tlsBase;                // Dereference to obtain the actual target pointer
    *(uint32_t*)((char*)tlsPtr + 0x34) = (uint32_t)value;   // Write value at offset 0x34
}