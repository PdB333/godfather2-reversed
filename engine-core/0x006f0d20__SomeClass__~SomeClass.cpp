// FUNC_NAME: SomeClass::~SomeClass
// Function address: 0x006f0d20
// Role: Destructor - frees three child objects stored at offsets +0x0c, +0x14, +0x1c
void __fastcall SomeClass::~SomeClass(void* thisPtr) {
    // Free member at +0x1c (e.g., component C)
    if (*(void**)((char*)thisPtr + 0x1c) != 0) {
        safeDelete((void**)((char*)thisPtr + 0x1c));
    }
    // Free member at +0x14 (e.g., component B)
    if (*(void**)((char*)thisPtr + 0x14) != 0) {
        safeDelete((void**)((char*)thisPtr + 0x14));
    }
    // Free member at +0x0c (e.g., component A)
    if (*(void**)((char*)thisPtr + 0x0c) != 0) {
        safeDelete((void**)((char*)thisPtr + 0x0c));
    }
    // No return value
}