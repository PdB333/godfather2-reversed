// FUNC_NAME: UnknownClass::constructor (0x008d0210)
// Constructor that initializes multiple vtable pointers (likely multiple inheritance or interface table) and calls base initializer.

void __thiscall UnknownClass::constructor(UnknownClass* this) {
    // Set primary vtable pointer at offset 0x00
    this->vtable = (void*)&PTR_FUN_00d7ce90;  // +0x00

    // Set secondary vtable pointer at offset 0x3C (0xF * 4)
    this->secondaryVtable1 = (void*)&PTR_LAB_00d7ce80;  // +0x3C

    // Set another vtable/data pointer at offset 0x48 (0x12 * 4)
    this->secondaryVtable2 = (void*)&PTR_LAB_00d7ce7c;  // +0x48

    // Call base class constructor (likely a parent or initializer)
    baseClassConstructor();  // 0x0083f920
    return;
}