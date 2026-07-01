// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x008ff3a0
// Role: Constructor for a derived class. Calls base constructor and optionally performs additional initialization based on a flag.

void __thiscall SomeClass::SomeClass(byte param_2) {
    // Call base class constructor (likely EARSObject or similar)
    BaseClass::BaseClass(); // FUN_008ff0c0

    // If the low bit of param_2 is set, perform extra initialization
    if ((param_2 & 1) != 0) {
        someInitializationFunction(this); // FUN_009c8eb0
    }

    // Return this pointer (implicit in C++ constructors)
}