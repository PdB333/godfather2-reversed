// FUNC_NAME: UnknownClass::~UnknownClass (destructor at 0x007ae1c0)

void __fastcall UnknownClass::~UnknownClass(UnknownClass* this) {
    // Set vtable to first vtable (likely derived class vtable)
    *(int*)this = (int)&PTR_LAB_00d6bbfc;

    // Release sound resource with ID 0x31
    FUN_007f6420(0x31);
    // Release sound resource with ID 0x22
    FUN_007f6420(0x22);

    // Check if a pointer at this+0x58 (this[0x16]) is non-null and not 0x48
    // The pointer points to an object with a field at offset 0xff0
    int* ptrAt58 = *(int**)((char*)this + 0x58);
    if (ptrAt58 != nullptr && *(int*)((char*)ptrAt58 + 0xff0) != 0x48) {
        // Release sound resource again if condition holds
        FUN_007f6420(0x22);
    }

    // Check flag at offset 0x20 (bit 1)
    if ((*(unsigned char*)((char*)this + 0x20) & 2) != 0) {
        // Call some cleanup function with global data
        FUN_007f4490(0, 0, DAT_00d5ef90);
        // Clear the flag
        *(unsigned char*)((char*)this + 0x20) &= ~2;
    }

    // Switch vtable to base class vtable
    *(int*)this = (int)&PTR_LAB_00d6b95c;

    // Call base class destructor
    FUN_0080ea60();
}