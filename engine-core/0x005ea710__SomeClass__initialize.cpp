// FUNC_NAME: SomeClass::initialize
// Address: 0x005ea710
// Role: Constructor/initializer for an unknown game object class. Sets a flag at +0x130 to 0 and calls two engine initialization routines.

int __fastcall SomeClass::initialize(int thisPtr)
{
    // Call base class constructor or engine initializer
    FUN_00abd570();

    // Set field at offset 0x130 to 0 (likely a flag or state indicator)
    *(int *)(thisPtr + 0x130) = 0;

    // Call another initializer with parameters 0 and 1 (e.g., component index, enable flag)
    FUN_00ab5fb0(0, 1);

    // Return this pointer (standard for constructors)
    return thisPtr;
}