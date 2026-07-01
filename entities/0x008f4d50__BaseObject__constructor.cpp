// FUNC_NAME: BaseObject::constructor
// Address: 0x008f4d50
// Role: Generic base class constructor with optional vtable initialization

undefined4 __thiscall BaseObject::constructor(BaseObject* this, byte flags)
{
    // Call base class initializer (likely sets up common fields, zeroes memory, etc.)
    this->baseInit();  // FUN_008f4070

    // If bit 0 of flags is set, perform vtable initialization (e.g., set up virtual function table pointer)
    if ((flags & 1) != 0) {
        this->vtableInit();  // FUN_009c8eb0
    }

    // Return the constructed object pointer
    return this;
}