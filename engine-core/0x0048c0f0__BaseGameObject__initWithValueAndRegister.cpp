// FUNC_NAME: BaseGameObject::initWithValueAndRegister
void __thiscall BaseGameObject::initWithValueAndRegister(BaseGameObject* this, uint32_t value) {
    // Store value at offset 0x34 (likely an ID or data member)
    this->field_0x34 = value;

    // Access global pool pointer: g_pGlobalPool is a global structure,
    // and offset 0x14 is a mutable pointer into a preallocated buffer.
    int** poolCursor = (int**)(g_pGlobalPool + 0x14);

    // Write the vtable address (PTR_LAB_01123d00) into the current slot
    **poolCursor = (int)&PTR_LAB_01123d00;

    // Advance pointer by 4 bytes (size of vtable pointer)
    (*poolCursor)++;

    // Write the value into the next slot
    *((uint32_t*)(*poolCursor)) = value;

    // Advance again for the next allocation
    (*poolCursor)++;
}