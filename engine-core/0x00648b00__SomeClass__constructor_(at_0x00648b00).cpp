// FUNC_NAME: SomeClass::constructor (at 0x00648b00)
void SomeClass::constructor(void* param1, void* param2) {
    // Check if the object's first byte is zero (uninitialized flag)
    if (*this == 0) {
        baseConstructor(); // FUN_00648930 - likely base class constructor
        *this = 1;         // Mark as initialized
    }

    // Set vtable pointer at offset +0x18c (396) to function FUN_00485380
    *(void (**)())(this + 0x18c) = FUN_00485380;
    // Set vtable pointer at offset +0x190 (400) to label LAB_004853b0
    *(void (**)())(this + 400) = &LAB_004853b0;
    // Set field at +0x194 (404) to unaff_EDI (some register value)
    *(int*)(this + 0x194) = unaff_EDI;

    // Store 'this' pointer at offset +0x64 (100)
    *(void**)(this + 100) = this;

    // Set vtable pointer at offset +0x68 (104) to FUN_00485380
    *(void (**)())(this + 0x68) = FUN_00485380;
    // Set vtable pointer at offset +0x6c (108) to label LAB_004853b0
    *(void (**)())(this + 0x6c) = &LAB_004853b0;
    // Set field at +0x70 (112) to unaff_EDI
    *(int*)(this + 0x70) = unaff_EDI;

    // Call another initialization function with the original parameters
    initSomething(param1, param2); // FUN_00648c60
}