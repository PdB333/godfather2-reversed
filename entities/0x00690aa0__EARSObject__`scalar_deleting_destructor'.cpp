// FUNC_NAME: EARSObject::`scalar deleting destructor'
// Address: 0x00690aa0
// Role: MSVC-style scalar deleting destructor. Calls the actual destructor (0x00690a00) and conditionally frees memory via operator delete (0x009c8eb0).
EARSObject* __thiscall EARSObject::scalar_deleting_destructor(unsigned char flags) {
    // Call the real destructor (e.g., ~EARSObject) at 0x00690a00
    this->~EARSObject();
    // If flag bit 0 is set, deallocate the object
    if ((flags & 1) != 0) {
        ::operator delete(this); // Scalable delete at 0x009c8eb0
    }
    return this; // Return the pointer for possible chaining
}