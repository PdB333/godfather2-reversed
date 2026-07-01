// FUNC_NAME: SomeClass::SomeClass
// Address: 0x007de550
// Role: Constructor for a derived class that sets up vtable pointers and calls base class constructor.
// Likely multiple inheritance: sets base vtable, calls base constructor, then sets own vtable, calls additional init.
void __fastcall SomeClass::SomeClass(void *thisPtr) // __fastcall with this in ECX
{
    // Set vtable pointer to base class vtable (before calling base constructor)
    *(int **)thisPtr = (int *)&PTR_LAB_00d6f6ac; // Base class vtable

    // Call base class constructor with some flag (0)
    FUN_007ab650(0); // BaseClass::BaseClass(0)

    // Now set vtable to derived class vtable (after base construction)
    *(int **)thisPtr = (int *)&PTR_LAB_00d6b95c; // Derived class vtable

    // Call additional initialization for derived class
    FUN_0080ea60(); // DerivedClass::someInit()
}