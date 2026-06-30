// FUNC_NAME: UnknownClass::~UnknownClass
// Function address: 0x0067f1c0
// Role: Destructor for an unknown class (likely from EARS engine). Sets vtable pointers, destroys a member at +0x4, sets global flag, and optionally deletes the object.

__thiscall void UnknownClass::~UnknownClass(UnknownClass* this, byte deletingFlag) {
    // Set vtable to first base class vtable
    this->vtable = &PTR_FUN_00d58188;

    // Destroy member at offset +0x4 (if non-null)
    if (this->field_0x4 != 0) {
        FUN_009c8f10(this->field_0x4); // Likely destructor of some sub-object
    }

    // Set vtable to second base class vtable (completing destruction chain)
    this->vtable = &PTR_LAB_00d580d4;

    // Reset global flag (likely a destruction-in-progress or reference counter)
    g_someGlobalFlag = 0;

    // If the deletingFlag indicates a delete operation, call operator delete
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this); // Likely operator delete
    }
}