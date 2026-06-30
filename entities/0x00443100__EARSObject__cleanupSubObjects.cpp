// FUNC_NAME: EARSObject::cleanupSubObjects
void __thiscall EARSObject::cleanupSubObjects(void) {
    // Retrieve vtable pointer stored at offset +0x7c (points to a function table)
    int* vtable = *(int**)((int)this + 0x7c);
    // Call the second virtual function (vtable[1]) on the child object at offset +0x6c
    typedef void (__thiscall *ReleaseMethod)(void* child, int arg);
    ReleaseMethod release = (ReleaseMethod)vtable[1];
    release(*(void**)((int)this + 0x6c), 0);

    // Nullify the child pointer
    *(int*)((int)this + 0x6c) = 0;
    // Nullify two additional pointers
    *(int*)((int)this + 0x74) = 0;
    *(int*)((int)this + 0x70) = 0;
}