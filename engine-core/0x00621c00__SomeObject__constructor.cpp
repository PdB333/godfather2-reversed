// FUNC_NAME: SomeObject::constructor
// Address: 0x00621c00
// Description: Constructor wrapper that calls initialization routine and returns this pointer.

int __thiscall SomeObject::constructor(int thisPtr) {
    // Call the actual initialization function (likely a base class constructor or setup)
    FUN_00622570();
    // Return the 'this' pointer as per convention
    return thisPtr;
}