// FUNC_NAME: UnknownClass::constructor
// Function at 0x008597e0: Constructor. Calls base class constructor at offset 8 from first member pointer, then local initialization.
void UnknownClass::constructor(int* thisPtr)
{
    // Call base constructor - first member (thisPtr[0]) points to base class instance, add 8 for subobject offset
    FUN_00859730(*(int*)(thisPtr) + 8);
    // Initialize own data
    FUN_00859680(thisPtr);
}