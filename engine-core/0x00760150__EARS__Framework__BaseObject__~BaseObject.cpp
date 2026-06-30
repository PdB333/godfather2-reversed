// FUNC_NAME: EARS::Framework::BaseObject::~BaseObject
// Address: 0x00760150
// Role: Destructor of a base object. Sets vtable to base class for proper cleanup,
// destroys a member at offset +4, switches vtable to purecall to prevent virtual calls
// during destruction, then optionally deallocates memory if the deleting flag is set.

undefined4* __thiscall EARS::Framework::BaseObject::~BaseObject(undefined4* this, byte deletingFlag)
{
    // Set vtable to base class vtable (likely EARSBaseObject or similar) for proper cleanup.
    *this = &PTR_LAB_00d653d4;

    // If the sub-object at offset 4 (e.g., a pointer to a child or allocated resource) exists, destroy it.
    if (this[1] != 0) {
        cleanupMember(this + 1);  // Calls destructor on the member at this+4
    }

    // After all cleanup, set vtable to purecall to prevent any virtual function calls from being dispatched.
    *this = &PTR___purecall_00e407a4;

    // If the scheduler indicates this is a deleting destructor (bit 0 set), free the memory.
    if ((deletingFlag & 1) != 0) {
        operatorDelete(this);  // Calls the appropriate deallocation function (likely ::operator delete)
    }

    return this;
}