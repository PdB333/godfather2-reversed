// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x00793050 - Destructor for a class with sub-object array (4 elements, 28 bytes each)
// Class layout: vtable at +0x00, unknown tables at +0x3C (0xf * 4) and +0x48 (0x12 * 4),
// sub-object array at +0x64 (0x19*4) through +0xB8 (0x2E*4)

void __fastcall SomeClass::~SomeClass(void* this) {
    // Set vtable and two function table pointers (likely default cleanup handlers)
    *(int**)this = &PTR_FUN_00d69e04;          // +0x00: vtable
    *(int**)((int*)this + 0xf) = &PTR_LAB_00d69df4;  // +0x3C
    *(int**)((int*)this + 0x12) = &PTR_LAB_00d69df0;  // +0x48

    // Loop over 4 sub-objects at offsets +0x64, +0x80, +0x9C, +0xB8 (each 28 bytes)
    int count = 3; // loop 4 times: 3,2,1,0
    int* pSubObj = (int*)this + 0x35; // start past the array (at +0xD4)
    do {
        pSubObj -= 7; // step back 28 bytes
        int* checkPtr = pSubObj;
        if (*checkPtr != 0) {
            // If sub-object is non-null, clean it up
            FUN_004daf90(pSubObj); // assumed cleanup function
        }
        count--;
    } while (count > -1);

    // Final cleanup
    FUN_0046c640(); // likely a global or static cleanup
}