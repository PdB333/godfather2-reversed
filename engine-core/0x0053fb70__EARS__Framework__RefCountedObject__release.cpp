// FUNC_NAME: EARS::Framework::RefCountedObject::release

void __thiscall EARS::Framework::RefCountedObject::release(void)
{
    RefCountedObject* thisPtr = this; // unaff_EDI
    
    // Release the object at offset 0x58: call a helper then virtual release
    FUN_009e61e0(*(void**)((char*)thisPtr + 0x58));
    if (*(void**)((char*)thisPtr + 0x58) != nullptr) {
        void* obj = *(void**)((char*)thisPtr + 0x58);
        (*(void(__thiscall**)(void*, int))(*(int*)obj))(obj, 1); // vtable[0] with arg 1
    }
    
    // Handle the ref-counted pointer at offset 0x54
    RefCountedObject* ptr54 = *(RefCountedObject**)((char*)thisPtr + 0x54);
    *(void**)((char*)thisPtr + 0x58) = nullptr; // reset
    if (*(short*)((char*)ptr54 + 4) != 0) { // check ref count at offset 4
        // decrement counter at offset 6
        *(short*)((char*)ptr54 + 6) = *(short*)((char*)ptr54 + 6) - 1;
        if (*(short*)((char*)ptr54 + 6) == 0) {
            (*(void(__thiscall**)(void*, int))(*ptr54))(ptr54, 1); // release
        }
    }
    
    // If a flag at +0x28 is set and an associated value at +0x2c is nonzero
    if (*(char*)((char*)thisPtr + 0x28) != '\0' && *(int*)((char*)thisPtr + 0x2c) != 0) {
        FUN_00540390(); // unknown cleanup
    }
    
    // Handle the ref-counted pointer at offset 0x24 (similar to offset 0x54)
    RefCountedObject* ptr24 = *(RefCountedObject**)((char*)thisPtr + 0x24);
    if (*(short*)((char*)ptr24 + 4) != 0) {
        *(short*)((char*)ptr24 + 6) = *(short*)((char*)ptr24 + 6) - 1;
        if (*(short*)((char*)ptr24 + 6) == 0) {
            (*(void(__thiscall**)(void*, int))(*ptr24))(ptr24, 1);
        }
    }
    *(void**)((char*)thisPtr + 0x24) = nullptr;
    
    // Call virtual method at vtable+8 on object at +0x10
    void* obj10 = *(void**)((char*)thisPtr + 0x10);
    if (obj10 != nullptr) {
        (*(void(__thiscall**)(void*, int, int))(*(int*)obj10 + 8))(obj10, 0, 0);
    }
    
    // TLS and resource cleanup with handle at +0x14
    int handle = *(int*)((char*)thisPtr + 0x14);
    TlsGetValue(DAT_01139810); // global TLS index
    FUN_00aa28e0(handle);
    FUN_00c6ed40();
    
    // Release the object at +0x10 if it exists
    if (obj10 != nullptr) {
        (*(void(__thiscall**)(void*, int))(*(int*)obj10 + 0x10))(obj10, 1);
    }
}