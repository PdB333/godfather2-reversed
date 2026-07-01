// FUNC_NAME: SomeClass::constructor
// Address: 0x00825180
// Role: Constructor initializing vtable and setting a float at offset 0x4c to sum of two source objects' floats at same offset.

extern "C" void FUN_008334a0(); // Base class constructor or initializer

class SomeClass
{
public:
    void* vptr; // +0x00 vtable pointer
    // ... other members (0x04 to 0x48) ...
    float someFloat; // +0x4c (offset 0x13 * 4)

    // Constructor: takes two source objects and sums their float at offset 0x4c
    SomeClass* __thiscall constructor(SomeClass* sourceA, SomeClass* sourceB)
    {
        // Call base class constructor (or some other initialization)
        FUN_008334a0();

        // Zero out the float field before summing
        this->someFloat = 0.0f;

        // Set vtable pointer (class-specific)
        this->vptr = &PTR_LAB_00d73448;

        // Sum the float values from the two source objects
        this->someFloat = *(float*)((unsigned char*)sourceB + 0x4c) + *(float*)((unsigned char*)sourceA + 0x4c);

        return this;
    }
};