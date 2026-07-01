// FUNC_NAME: releaseChildAndDestruct
void __fastcall releaseChildAndDestruct(void* thisPtr) {
    // +0x00: vtable pointer
    // +0x04: owned child object pointer
    void** vtable = *(void***)thisPtr;
    void* child = *(void**)((char*)thisPtr + 4);

    if (child != 0) {
        // Call virtual release/destroy on child (vtable+4) with flag 0
        ((void (__fastcall*)(void*, int))vtable[1])(child, 0);
        *(void**)((char*)thisPtr + 4) = 0;
    }

    // Call virtual destructor at vtable+0xc
    ((void (__fastcall*)(void*))vtable[3])();
}