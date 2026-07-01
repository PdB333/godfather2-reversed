// FUNC_NAME: DataTransfer::copyFields
// Address: 0x0084dee0
// Copies structured data from source (param_2) to destination (this).
// The source layout: [0:subObj1(?), 8:subObj2(?), 0x10:block96(96B), 0x1c:block96(96B), 0x28..0x40:ptrList[7] (pointers to 32B blocks)]

void __thiscall DataTransfer::copyFields(void* this, void* src) {
    int iVar1; // base of src

    iVar1 = (int)src;

    // Copy first sub‑object (likely a string or small struct) from src+0
    copySubObject(this, src);
    // Copy second sub‑object from src+8
    copySubObject(this, (void*)(iVar1 + 8));

    // Copy 96 bytes from src+0x10 (e.g., a large array or embedded struct)
    memcpyBlock(0x60, (void*)(iVar1 + 0x10));
    // Copy another 96 bytes from src+0x1c (overlaps? but offsets are distinct)
    memcpyBlock(0x60, (void*)(iVar1 + 0x1c));

    // Copy 7 blocks of 32 bytes each; the source pointers are stored at offsets 0x28..0x40
    {
        uint* pPtr;
        pPtr = *(uint**)(iVar1 + 0x28); // +0x28
        memcpyBlock(0x20, pPtr);
        pPtr = *(uint**)(iVar1 + 0x2c); // +0x2c
        memcpyBlock(0x20, pPtr);
        pPtr = *(uint**)(iVar1 + 0x30); // +0x30
        memcpyBlock(0x20, pPtr);
        pPtr = *(uint**)(iVar1 + 0x34); // +0x34
        memcpyBlock(0x20, pPtr);
        pPtr = *(uint**)(iVar1 + 0x38); // +0x38
        memcpyBlock(0x20, pPtr);
        pPtr = *(uint**)(iVar1 + 0x3c); // +0x3c
        memcpyBlock(0x20, pPtr);
        pPtr = *(uint**)(iVar1 + 0x40); // +0x40
        memcpyBlock(0x20, pPtr);
    }
    return;
}