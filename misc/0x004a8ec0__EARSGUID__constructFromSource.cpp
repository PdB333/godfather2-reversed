// FUNC_NAME: EARSGUID::constructFromSource
// 0x004a8ec0
// Initializes a 64-bit GUID (two 32-bit fields) with a default magic value.
// If a source object is provided, copies its GUID via a virtual method call at vtable+0x4.
EARSGUID* __thiscall EARSGUID::constructFromSource(EARSGUID* source) {
    // +0x00: low 32 bits of GUID (data[0])
    // +0x04: high 32 bits of GUID (data[1])
    data[0] = 0xFE16702F;
    data[1] = 0;

    if (source != nullptr) {
        // source is a polymorphic object; its vtable pointer is at offset 0.
        // Virtual function at vtable+4 likely returns a pointer to the source's GUID.
        void** vtable = *(void***)source;
        typedef EARSGUID* (__thiscall* GUIDCopyFunc)(void* buffer);
        GUIDCopyFunc copyFunc = (GUIDCopyFunc)vtable[1];  // offset 4 = index 1
        EARSGUID* pGUID = copyFunc(source);               // call with local_8 buffer? Actually arg is local_8, but decompiler shows local_8 as target? Recheck
        // According to decompiler: puVar1 = (undefined4*)(**(code**)(*param_2+4))(local_8);
        // This means copyFunc is called with local_8 as the argument, but local_8 is a 8-byte stack buffer (undefined1 local_8[8]).
        // The function returns a pointer, and the result is copied from that pointer.
        // This suggests that copyFunc takes a buffer (likely to write the GUID) and returns a pointer to the buffer or the actual GUID.
        // Since it's a common pattern, I'll treat it as: copyFunc(local_8) returns a pointer to a GUID structure (maybe local_8 itself?).
        // For simplicity, we assume the function writes to local_8 and returns it.
        // Actually: *(undefined4 *)(**(code **)(*param_2 + 4))(local_8) - it calls the function, then dereferences the return value as two 32-bit values.
        // But the decompiler shows: puVar1 = (undefined4 *)(...)(local_8); then *param_1 = *puVar1; param_1[1] = puVar1[1];
        // So very likely the virtual function returns a pointer to a 8-byte GUID structure.
        // It's possible that the virtual function's implementation uses local_8 as a temporary and returns it.
        // To match the decompiler, we'll allocate a local temporary and then copy.
        
        // Actually, let's reconstruct more faithfully:
        // We have a local 8-byte buffer (local_8) that is passed to the virtual function.
        // The virtual function likely writes the GUID into that buffer and returns its address.
        // So we call with a stack buffer:
        EARSGUID tempBuffer;            // 8 bytes
        EARSGUID* pGUID = ((GUIDCopyFunc)((code**)vtable)[1])(&tempBuffer);
        // Then copy from pGUID:
        data[0] = pGUID->data[0];
        data[1] = pGUID->data[1];
    }

    return this;
}