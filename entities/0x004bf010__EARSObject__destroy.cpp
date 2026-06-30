// FUNC_NAME: EARSObject::destroy
void * __thiscall EARSObject::destroy(byte flag) {
    // Call base class destructor or finalization logic
    // FUN_004bf030 - likely a virtual destructor or cleanup member
    finalize();
    // If the object was heap-allocated (flag bit 0 set), free the memory
    // FUN_009c8eb0 - custom operator delete or global free
    if ((flag & 1) != 0) {
        operator delete(this);
    }
    return this;
}