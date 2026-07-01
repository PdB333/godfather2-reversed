// FUNC_NAME: SomeClass::~SomeClass
void __thiscall SomeClass::~SomeClass(void)
{
    // Set vtable pointer to a base/destructor vtable (likely reverting to a deleted state)
    this[0] = &PTR_FUN_00d8045c;
    // Set method pointers at offsets +0x3C and +0x48 (0x0F * 4 = 0x3C, 0x12 * 4 = 0x48)
    this[0x0F] = &PTR_LAB_00d8044c;
    this[0x12] = &PTR_LAB_00d80448;
    // If member at +0x60 (0x18 * 4) is not null, call member at +0x6C (0x1B * 4) as a cleanup function
    if (this[0x18] != 0) {
        ((code (*)(void *))this[0x1B])(this[0x18]);
    }
    // Call base cleanup / memory deallocation
    FUN_0046c640();
    return;
}