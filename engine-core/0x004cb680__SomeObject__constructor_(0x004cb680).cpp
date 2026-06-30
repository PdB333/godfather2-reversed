// FUNC_NAME: SomeObject::constructor (0x004cb680)
// Class constructor with conditional destructor call based on flag.
// Sets vtable pointer, calls base initializer, and optionally calls destructor if (flag & 1).
// Vtable at PTR_LAB_00e36658
// Callee FUN_00654d40 is likely base class constructor.
// Callee FUN_009c8eb0 is likely destructor.

class SomeObject {
public:
    // Vtable pointer (offset +0x00)
    void *vtable;
    // ... other members ...

    // Constructor: param2 is a flag (1 = call destructor after init, else normal construction)
    SomeObject *__thiscall constructor(byte param2);
};

extern void *PTR_LAB_00e36658; // Vtable for SomeObject
extern void __thiscall FUN_00654d40(void); // Base constructor
extern void __thiscall FUN_009c8eb0(SomeObject *obj); // Destructor

// Reconstructed constructor
SomeObject *__thiscall SomeObject::constructor(byte param2) {
    // Set vtable pointer
    this->vtable = &PTR_LAB_00e36658;

    // Call base class constructor
    FUN_00654d40();

    // If flag low bit is set, call destructor (e.g., for placement new with destruction)
    if ((param2 & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}