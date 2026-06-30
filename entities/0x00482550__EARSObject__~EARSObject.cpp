// FUNC_NAME: EARSObject::~EARSObject
undefined4* __thiscall EARSObject::~EARSObject(undefined4* this, byte shouldDelete) {
    // Free resources at offsets +0x1C (+28 bytes), +0x10 (+16 bytes), +0x04 (+4 bytes)
    if (this[7] != 0) {
        releaseResource((void*)this[7]);  // FUN_009c8f10
    }
    if (this[4] != 0) {
        releaseResource((void*)this[4]);  // FUN_009c8f10
    }
    if (this[1] != 0) {
        releaseResource((void*)this[1]);  // FUN_009c8f10
    }
    // Restore vtable to base class (PTR_LAB_00e33658)
    *this = &baseClassVtable;
    // Clear global singleton or manager flag
    gSomeGlobalCount = 0;  // DAT_01223490
    // Optionally deallocate memory if delete flag is set
    if ((shouldDelete & 1) != 0) {
        operatorDelete(this);  // FUN_009c8eb0
    }
    return this;
}