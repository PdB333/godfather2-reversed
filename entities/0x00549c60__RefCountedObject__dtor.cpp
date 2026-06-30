// FUNC_NAME: RefCountedObject::dtor
undefined4* __thiscall RefCountedObject::dtor(undefined4* this, byte deleteFlag)
{
    // RefCountBlock is a structure allocated separately for reference counting
    struct RefCountBlock {
        void (__thiscall* dtor)(int);   // +0x00: virtual destructor of the block
        short field_4;                  // +0x04: some active flag or reference count
        short field_6;                  // +0x06: reference count to decrement
    };

    RefCountBlock* block = (RefCountBlock*)this[0x30]; // +0x30: pointer to reference counter block

    // Set vtable to base class (scalar deleting destructor pattern)
    *this = (undefined4*)&PTR_FUN_00e39bc8;

    if (block != nullptr) {
        // If the block's flag at +0x04 is non‑zero, decrement the count at +0x06
        if (block->field_4 != 0) {
            block->field_6--;
            if (block->field_6 == 0) {
                // Reference count reached zero – call the block’s destructor with argument 1 (delete)
                block->dtor(1);
            }
        }
        // Release the reference to the block
        this[0x30] = 0;
    }

    // If the delete flag’s lowest bit is set, free the object memory
    if ((deleteFlag & 1) != 0) {
        FUN_009c8eb0(this); // Likely operator delete or custom deallocator
    }

    return this;
}