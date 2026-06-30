// FUNC_NAME: EARSString::c_str
uint __thiscall EARSString::cStr(void* this, uint param_1, uint param_2) {
    // +0x14: m_pHeapBuffer (allocated buffer if large)
    // +0x24: m_pSharedData (pointer to reference-counted shared block)
    // +0x1c: m_flags (bit0 = inline/small string; likely 0 means external/heap)
    // +0x30: m_nDataOffset (offset to character data within shared block)

    int* thisPtr = (int*)this;
    if ((thisPtr[0x14] == 0) && (thisPtr[0x24] == 0)) {
        // Both buffers null → return address of this object with lower byte cleared
        // This may be the inline short string storage (e.g. in the object itself)
        return (uint)this & 0xFFFFFF00U;
    }

    if (thisPtr[0x1c] == 0) {
        int buffer = 0;
        if (thisPtr[0x14] != 0) {
            // Access thread-local storage (FS segment at offset 0x2c) for some magic pointer
            // Used for null/NULL check or special sentinel
            int* tlsBase = *(int**)(__readfsdword(0x2c)); // TLS base pointer
            int* tlsValue = (int*)*tlsBase;
            buffer = tlsValue[8] + thisPtr[0x14]; // Add to heap buffer
        }
        if (buffer == 0) {
            // Fallback to virtual function call on the shared block (at +0x24)
            // It calls a method at offset 0x18 (likely 'getData' or 'c_str')
            int* sharedBlock = (int*)thisPtr[0x24];
            if (sharedBlock != 0) {
                int (__thiscall* virtualFunc)(void*, uint, uint) = (int (__thiscall*)(void*, uint, uint))sharedBlock[6]; // +0x18/4 = index 6
                return (uint)virtualFunc((void*)sharedBlock, param_1, param_2);
            }
            return 0;
        }
    }

    // Default: call helper function on shared block + offset
    return FUN_00518f00(thisPtr[0x24] + 0x30);
}