// FUNC_NAME: UnknownClass::UnknownClass
// Function address: 0x008eba70
// Role: Constructor - calls initialization function and returns this pointer

void __thiscall UnknownClass::UnknownClass() {
    // Calls initialization routine at 0x008ea1d0
    initialize();
    // return this; // implicit in __thiscall constructor
}