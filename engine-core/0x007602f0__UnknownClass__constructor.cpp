// FUNC_NAME: UnknownClass::constructor
// Address: 0x007602f0
// Role: Constructor for an unknown EA EARS engine object (size 0x30).
// The class stores four parameters (param2, param3, param4, param5) and a global value.
// It also zeros several fields and frees any previously allocated resource at offset +0x04.
// Note: The decompiler may have reordered instructions; the if block appears dead as written.

class UnknownClass {
public:
    void* vtable;                // +0x00
    void* resourcePtr;           // +0x04 (pointer to some allocated resource, may be freed)
    int field_08;                // +0x08
    int field_0C;                // +0x0C
    int param2;                  // +0x10
    int field_14;                // +0x14
    int field_18;                // +0x18
    int field_1C;                // +0x1C
    int param4;                  // +0x20
    int param3;                  // +0x24
    int globalValue;             // +0x28 (initialized from DAT_00d5ddec)
    int param5;                  // +0x2C
};

// Global variable from the game (likely a singleton or constant)
extern int DAT_00d5ddec;

// Constructor
UnknownClass* __thiscall UnknownClass::constructor(UnknownClass* this, int param2, int param3, int param4, int param5)
{
    // Set vtable pointer
    this->vtable = (void*)&PTR_FUN_00d65404;   // vtable address

    // Pointer at +0x04 – possibly a previously allocated resource
    int* ptr = (int*)&this->resourcePtr;
    *ptr = 0;                                    // Set pointer to null (possibly overwrites old value)

    this->field_08 = 0;
    this->field_0C = 0;
    this->param2 = param2;

    // If the resource pointer was not null, free it and set to null
    if (this->resourcePtr != 0) {
        // FUN_004daf90 is likely a deallocation routine for the resource
        FUN_004daf90(&this->resourcePtr);
        this->resourcePtr = 0;
    }

    // Zero remaining fields
    this->field_0C = 0;
    this->field_1C = 0;
    this->field_18 = 0;
    this->field_14 = 0;

    // Store parameters (note: order in class fields is as given, not necessarily logical)
    this->param3 = param3;    // +0x24
    this->param4 = param4;    // +0x20
    this->param5 = param5;    // +0x2C
    this->globalValue = DAT_00d5ddec;  // +0x28

    return this;
}