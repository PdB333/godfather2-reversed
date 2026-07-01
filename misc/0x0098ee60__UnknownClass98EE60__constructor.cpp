// FUNC_NAME: UnknownClass98EE60::constructor
// Constructor for a class with multiple inheritance (three vtables). 
// Address: 0x0098ee60
// Initializes base class via FUN_0046c590, sets vtables, zeroes fields.

// Unknown class size at least 0x80 bytes.
// Offsets:
// +0x00: vtable for derived class (PTR_FUN_00d91ad4)
// +0x3C: vtable pointer for first base (PTR_LAB_00d91ac4)
// +0x48: vtable pointer for second base (PTR_LAB_00d91ac0)
// +0x50..+0x7C: zeroed data (ints and shorts)

void * __thiscall UnknownClass98EE60::constructor(void *this, int someParam) {
    // Call base class constructor (assumed one parameter)
    FUN_0046c590(someParam); // Likely base class initializer

    // Set vtable for this class
    *(void **)this = (void *)&PTR_FUN_00d91ad4;

    // Set vtables for multiply-inherited base classes
    *(void **)((char *)this + 0x3C) = (void *)&PTR_LAB_00d91ac4;
    *(void **)((char *)this + 0x48) = (void *)&PTR_LAB_00d91ac0;

    // Zero fields from offset 0x50 to 0x7C
    *(int *)((char *)this + 0x50) = 0; // param_1[0x14]
    *(short *)((char *)this + 0x54) = 0; // *(undefined2*)(param_1 + 0x15)
    *(short *)((char *)this + 0x56) = 0; // *(undefined2*)((int)param_1 + 0x56)
    *(int *)((char *)this + 0x58) = 0; // param_1[0x16]
    *(short *)((char *)this + 0x5C) = 0; // *(undefined2*)(param_1 + 0x17)
    *(short *)((char *)this + 0x5E) = 0; // *(undefined2*)((int)param_1 + 0x5e)
    *(int *)((char *)this + 0x60) = 0; // param_1[0x18]
    *(int *)((char *)this + 0x64) = 0; // param_1[0x19]
    *(int *)((char *)this + 0x68) = 0; // param_1[0x1a]
    *(int *)((char *)this + 0x6C) = 0; // param_1[0x1b]
    *(int *)((char *)this + 0x70) = 0; // param_1[0x1c]
    *(int *)((char *)this + 0x74) = 0; // param_1[0x1d]
    *(int *)((char *)this + 0x78) = 0; // param_1[0x1e]
    *(int *)((char *)this + 0x7C) = 0; // param_1[0x1f]

    return this;
}