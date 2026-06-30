// FUNC_NAME: getFieldAt0x70
int __fastcall getFieldAt0x70(void* thisPtr) {
    // Returns the 4-byte value at offset 0x70 from the object pointer.
    // Likely a pointer or handle to an associated component or data.
    return *(int*)((char*)thisPtr + 0x70);
}