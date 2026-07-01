// FUNC_NAME: SimBase::~SimBase
void __fastcall SimBase::~SimBase(void* this) {
    uint flags;
    *(void**)this = &PTR_LAB_00e397fc; // set vtable to base destructor vtable
    flags = *(uint*)((int)this + 0x18); // offset +0x18: allocation flags/size info
    if ((int)flags >= 0) {
        TlsGetValue(DAT_01139810); // retrieve thread-local memory pool handle
        FUN_00aa26e0(
            *(void**)((int)this + 0x10), // pointer to allocated block at +0x10
            (flags & 0x3fffffff) * 0x30, // size: low 30 bits * 0x30 (48 bytes per unit)
            0x17                       // constant (likely alignment or pool ID)
        );
    }
    *(void**)this = &PTR_LAB_00dc4710; // set final vtable (destructor complete)
}