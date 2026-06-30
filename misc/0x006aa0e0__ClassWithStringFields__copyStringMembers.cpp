// FUNC_NAME: ClassWithStringFields::copyStringMembers
// Function address: 0x006aa0e0
// This function appears to copy string pointers from internal source members (offsets 0x4, 0x14, 0x24, 0x34)
// to storage members (offsets 0x44, 0x4c, 0x54, 0x5c), with default fallback if source is null.
// The byte at offset 0x68 is cleared, possibly indicating that copy is needed or has been performed.

// Assume FUN_004089b0 is a string copy operation (e.g., custom strcpy or pointer assignment)
extern void stringCopy(void* dest, const void* src); // placeholder for FUN_004089b0

// Default string constant when source pointer is null
extern const char defaultString; // DAT_0120546e

void copyStringMembers(void* this_ptr) {
    // Save this pointer for clarity
    // Offsets relative to this pointer (0x68: flag, 0x4,0x14,0x24,0x34: source pointers, 0x44,0x4c,0x54,0x5c: dest pointers)
    
    // Clear the flag at +0x68
    *(uint8_t*)((uintptr_t)this_ptr + 0x68) = 0;

    // Copy first string: source at +0x4 -> dest at +0x44
    const char* src1 = *(const char**)((uintptr_t)this_ptr + 4);
    if (src1 == nullptr) {
        src1 = &defaultString;
    }
    stringCopy((void*)((uintptr_t)this_ptr + 0x44), src1);

    // Copy second string: source at +0x14 -> dest at +0x4c
    const char* src2 = *(const char**)((uintptr_t)this_ptr + 0x14);
    if (src2 == nullptr) {
        src2 = &defaultString;
    }
    stringCopy((void*)((uintptr_t)this_ptr + 0x4c), src2);

    // Conditional copy: if integer at +0x28 is non-zero, copy source at +0x24 to dest at +0x54
    if (*(int*)((uintptr_t)this_ptr + 0x28) != 0) {
        const char* src3 = *(const char**)((uintptr_t)this_ptr + 0x24);
        if (src3 == nullptr) {
            src3 = &defaultString;
        }
        stringCopy((void*)((uintptr_t)this_ptr + 0x54), src3);
    }

    // Conditional copy: if integer at +0x38 is non-zero, copy source at +0x34 to dest at +0x5c
    if (*(int*)((uintptr_t)this_ptr + 0x38) != 0) {
        const char* src4 = *(const char**)((uintptr_t)this_ptr + 0x34);
        if (src4 == nullptr) {
            src4 = &defaultString;
        }
        stringCopy((void*)((uintptr_t)this_ptr + 0x5c), src4);
    }
}