// FUNC_NAME: EARS::Object::Object
// Address: 0x00773b90
// Role: Constructor with allocation flag. Calls base constructor, then conditionally calls destructor if flag indicates allocated memory (bit 0 set).
// This pattern is common in EA EARS engine for placement new/delete handling.

undefined4 __thiscall EARS::Object::Object(undefined4 this, byte allocFlag)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    FUN_007738d0();

    // If the object was allocated (bit 0 set), call destructor to free memory
    // This is a safety measure: if construction fails, the allocated memory is released.
    if ((allocFlag & 1) != 0) {
        FUN_00624da0(this); // Destructor / deallocation function
    }

    return this;
}