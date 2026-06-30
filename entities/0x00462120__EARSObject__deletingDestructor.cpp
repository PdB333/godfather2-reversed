// FUNC_NAME: EARSObject::deletingDestructor
void __thiscall EARSObject::deletingDestructor(byte flags) {
    // Call the real destructor (FUN_00462140)
    this->~EARSObject();
    // If the flag's lowest bit is set, free the memory via custom allocator (FUN_009c8eb0)
    if (flags & 1) {
        EARSHeap::free(this);
    }
}