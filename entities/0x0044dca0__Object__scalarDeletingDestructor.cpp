// FUNC_NAME: Object::scalarDeletingDestructor
// This is the scalar deleting destructor for an object of size 0x70 (112 bytes).
// The second parameter (deallocFlag) controls whether memory deallocation occurs.
// If bit 0 is set, the allocator's delete function is called with the object size.

void* __thiscall Object::scalarDeletingDestructor(void* this, unsigned char deallocFlag)
{
    // Call the actual destructor body (FUN_0044dcd0)
    ((void (__thiscall*)(void*))0x0044dcd0)(this);

    // If deallocation is requested (bit 0 set), free the memory
    if ((deallocFlag & 1) != 0) {
        // Get the allocator's vtable (FUN_009c8f80 returns a pointer to it)
        int* allocatorVtable = (int*)FUN_009c8f80();
        // The delete function is at vtable offset +4 (second entry)
        void (__thiscall* dealloc)(void*, int) = (void (__thiscall*)(void*, int))(allocatorVtable[1]);
        dealloc(this, 0x70); // object size = 0x70
    }

    return this;
}