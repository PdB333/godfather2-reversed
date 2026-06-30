// FUNC_NAME: RefCounted::addRef
uint32 __fastcall RefCounted::addRef(void* this) {
    // Increment reference count at offset +0x4 and return new value
    *(uint32*)((char*)this + 4) = *(uint32*)((char*)this + 4) + 1;
    return *(uint32*)((char*)this + 4);
}