// FUNC_NAME: UnknownClass::~UnknownClass
// Address: 0x0073da60
// Destructor for UnknownClass. Deletes internal members and optionally frees the object itself.

void __thiscall UnknownClass::~UnknownClass(void *this, byte shouldDelete)
{
    // Set vtable to base class pointer
    *(unknown **)this = &PTR_LAB_00d63778;

    // Free member at offset +0x64 (param_1[0x19]) if non-null
    if (*(void **)((int)this + 0x64) != (void *)0x0) {
        deleteMember((int)this + 0x64); // FUN_004daf90
    }

    // Free member at offset +0x5C (param_1[0x17]) if non-null
    if (*(void **)((int)this + 0x5C) != (void *)0x0) {
        deleteMember((int)this + 0x5C); // FUN_004daf90
    }

    // Additional cleanup (likely virtual table or base class)
    cleanupExtra(); // FUN_0080ea60

    // Optionally deallocate this object if flag is set
    if ((shouldDelete & 1) != 0) {
        operatorDelete(this); // FUN_00624da0
    }
}