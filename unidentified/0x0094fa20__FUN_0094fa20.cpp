//FUNC_NAME: SomeClass::SomeClass
// Address: 0x0094fa20
// Role: Constructor for SomeClass, with optional allocation of a 0x6c-byte subobject

class SomeClass : public BaseClass {
public:
    // Constructor: calls base class constructor, then conditionally allocates/initializes
    // a subobject of size 0x6c if param_2's bit 0 is set.
    // param_2: byte flag (bit 0 indicates whether to allocate)
    SomeClass(byte param_2);
};

// Base class constructor (FUN_0094f970)
// Assumed to be a __thiscall that initializes base members
void BaseClass::BaseClass();

// Function to allocate/initialize a subobject of given size at this pointer
// (FUN_0043b960) - likely a placement new or custom initializer
void SomeClass::initSubobject(void* thisPtr, uint size);

SomeClass::SomeClass(byte param_2) {
    // Call base class constructor
    BaseClass::BaseClass();

    // If bit 0 of param_2 is set, allocate/initialize a subobject of size 0x6c
    if ((param_2 & 1) != 0) {
        initSubobject(this, 0x6c); // +0x6c size subobject
    }
}