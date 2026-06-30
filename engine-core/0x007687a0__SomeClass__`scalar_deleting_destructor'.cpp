// FUNC_NAME: SomeClass::`scalar deleting destructor'
void* __thiscall SomeClass::scalarDeletingDestructor(void* this, byte flags)
{
    // Set vtable to first base (or derived) vtable
    *(void**)this = (void*)0x00d65aa8; // vtable pointer A; +0x00
    // Call derived destructor step (likely cleanup of derived members)
    FUN_00716310(); // derived destructor helper
    // Set vtable to base vtable (to avoid virtual calls during base destruction)
    *(void**)this = (void*)0x00d63090; // vtable pointer B; +0x00
    // Destroy member at offset 0x68 (0x1a * 4) if it exists
    if (*(void**)((char*)this + 0x68) != 0) {
        // Likely deletion of a pointer member (e.g., a string or child object)
        FUN_004daf90((int*)((char*)this + 0x68)); // destructor/free for member
    }
    // Call base class destructor (EARS common base destructor)
    FUN_0080ea60(); // base destructor (e.g., EARS::Object::~Object)
    // If the object was allocated on heap, free the memory
    if ((flags & 1) != 0) {
        FUN_00624da0(this); // operator delete(void*)
    }
    return this;
}