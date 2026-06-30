// FUN_004111a0: StringManager::getString

void __thiscall StringManager::getString(char *dest, byte maxLen) {
    // local_10 is a smart pointer or scoped reference for temporary string handle
    int scopedRef[3]; // +0x00: ref count or handle, rest unknown
    code *destructorFunc; // function pointer for cleanup

    // Retrieve internal string buffer pointer via helper
    int *internalPtr = (int *)getInternalStringPointer(scopedRef, this);
    char *src = (char *)*internalPtr;
    if (src == (char *)0x0) {
        src = &defaultEmptyString; // DAT_0120546e
    }
    strcpy_s(dest, maxLen, src); // safe copy with size check

    // Cleanup if handle is valid (e.g., decrement reference count)
    if (scopedRef[0] != 0) {
        destructorFunc(scopedRef[0]);
    }
}