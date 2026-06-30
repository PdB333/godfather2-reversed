// FUNC_NAME: SomeClass::SomeClass

// Constructor with flags. Base constructor is called first.
// If flag bit 0 is set, an additional initialization with size 0xd0 is performed.
// This pattern is common for objects that support both stack and heap allocation.

__thiscall SomeClass::SomeClass(uint flags)
{
    // Call base class constructor
    FUN_006eb400(); // BaseClass::BaseClass()

    if ((flags & 1) != 0)
    {
        // Perform memory-related initialization (likely heap allocation or registration)
        FUN_0043b960(this, 0xd0); // size = 208 bytes (0xd0)
    }

    return this;
}