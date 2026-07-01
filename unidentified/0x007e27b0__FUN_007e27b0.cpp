// FUNC_NAME: UnknownClass::~UnknownClass (scalar deleting destructor)
// Address: 0x007e27b0
// Role: Destructor that calls the actual destructor body and optionally deallocates memory.
// The byte parameter param_2 indicates whether to call operator delete (bit 0 set).

int* __thiscall UnknownClass::~UnknownClass(int* this, byte deleteFlag)
{
    // If the object's first field (likely a pointer or reference count) is non-null,
    // call the actual destructor body to release resources.
    if (*this != 0) {
        UnknownClass::destructorBody(this);  // FUN_004daf90
    }

    // If the delete flag (bit 0) is set, deallocate the memory.
    if ((deleteFlag & 1) != 0) {
        UnknownClass::operatorDelete(this);  // FUN_009c8eb0
    }

    return this;
}