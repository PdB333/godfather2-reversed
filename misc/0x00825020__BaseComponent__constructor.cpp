// FUNC_NAME: BaseComponent::constructor
// Function address: 0x00825020
// Role: Constructor for a component class. Calls base class constructor (FUN_008334a0), sets vtable pointer, and initializes a member at offset 0x4C to 0.

BaseComponent* __fastcall BaseComponent::constructor(BaseComponent* this)
{
    // Call base class constructor (likely a common initialization routine)
    FUN_008334a0();

    // Set vtable pointer to the class's virtual function table
    *this = (BaseComponent*)&PTR_LAB_00d73448;

    // Initialize member at offset 0x4C (index 0x13 in 4-byte units) to 0
    this->field_0x4C = 0; // +0x4C

    return this;
}