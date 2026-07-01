// FUNC_NAME: ManagerClass::~ManagerClass (destructor at 0x84ae10)
// This is a destructor that handles both scalar and vector deletion (param_2 bit 1 flag)
// It first sets the vtable to a base class (PTR_FUN_00d74d3c), releases a resource at offset +0x8,
// then sets vtable to derived (PTR_LAB_00d74d38), clears a global singleton flag (DAT_0112a590),
// and optionally calls operator delete via FUN_009c8eb0 if the flag indicates deletion.

undefined4* __thiscall ManagerClass::~ManagerClass(undefined4* this, byte deletingFlag)
{
    // Set vtable to base class (matching multiple inheritance or custom vtable switching)
    *this = &PTR_FUN_00d74d3c;

    // Release resource stored at offset +0x8 (e.g. a pointer to allocated memory or a subsystem handle)
    if (this[2] != 0) {
        FUN_009c8f10(this[2]);  // Release/destroy resource at +0x8
    }

    // Switch vtable back to derived class (vtable for the class being destroyed)
    *this = &PTR_LAB_00d74d38;

    // Reset global flag indicating this manager instance is active (likely singleton)
    DAT_0112a590 = 0;

    // If the deleting flag's LSB is set, free the memory (scalar or vector delete)
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this);  // operator delete
    }

    return this;
}