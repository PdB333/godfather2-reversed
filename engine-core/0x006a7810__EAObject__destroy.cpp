// FUNC_NAME: EAObject::destroy
int __thiscall EAObject::destroy(int this, unsigned char destroyFlag) {
    // This+0x8 holds a pointer to a managed resource (allocator/subobject)
    // Call cleanup function on that resource (likely its destructor or deallocator)
    FUN_009c8f10(*(void**)(this + 0x8));

    // If the flag's least significant bit is set, also deallocate this object itself
    if ((destroyFlag & 1) != 0) {
        FUN_009c8eb0(this); // Custom deallocation / operator delete
    }

    // Return the original pointer (note: invalid after deallocation, but follows asm pattern)
    return this;
}