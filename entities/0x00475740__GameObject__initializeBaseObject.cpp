// FUNC_NAME: GameObject::initializeBaseObject
void* __thiscall GameObject::initializeBaseObject(void* this, void* baseObject) {
    // Call base class initialization with a large buffer size (0x4000 = 16384 bytes)
    // This likely allocates or initializes a memory pool for the object
    FUN_0046e6b0(baseObject, 0x4000);

    // Set vtable pointer for this object (offset +0x00)
    this->vtable = (VTable*)&PTR_FUN_00e32be8;

    // Set member pointers at various offsets (likely function pointers or data tables)
    // +0x3C (offset 15 * 4)
    this->field_0x3C = (void*)&PTR_LAB_00e32d34;
    // +0x48 (offset 18 * 4)
    this->field_0x48 = (void*)&PTR_LAB_00e32d44;
    // +0x50 (offset 20 * 4)
    this->field_0x50 = (void*)&PTR_LAB_00e32d48;
    // +0x54 (offset 21 * 4)
    this->field_0x54 = (void*)&PTR_LAB_00e32d50;
    // +0x58 (offset 22 * 4)
    this->field_0x58 = (void*)&PTR_LAB_00e32db0;

    return this;
}