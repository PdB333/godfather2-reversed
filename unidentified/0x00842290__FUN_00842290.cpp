// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x00842290
// Role: Constructor for SomeClass, calls base class init and optionally additional init based on flag.

class SomeClass {
public:
    // Constructor: takes a flag (allocFlag) that controls whether to call additional initialization.
    // If allocFlag & 1 is set, calls FUN_00840230 (likely a secondary constructor or allocation routine).
    __thiscall SomeClass(byte allocFlag) {
        // Call base class constructor or common initialization (FUN_00848860)
        FUN_00848860();

        // If the lowest bit of allocFlag is set, perform additional initialization
        if ((allocFlag & 1) != 0) {
            FUN_00840230(this); // +0x0: this pointer passed as argument
        }

        // Return this pointer (implicit in constructor)
        return this;
    }
};