// FUNC_NAME: Player::Player
// Address: 0x005418b0
// Role: Constructor for the main Player class, sets up multiple interface vtable pointers,
// initializes a helper callback object, and performs engine-specific startup tasks.

void * __thiscall Player::Player(Player *this, uint someParam) {
    void *helperObj;

    // Initialize type/resource with flag 0x4000 (likely set name or type ID)
    engineFunc_0x0046e6b0(someParam, 0x4000);

    // Set main vtable pointer (offset 0x00)
    this->vtable = (void *)&PTR_FUN_00e392a0;

    // Set interface vtable pointers at various offsets:
    // +0x3C (0xf*4): interface A
    // +0x48 (0x12*4): interface B
    // +0x50 (0x14*4): interface C
    // +0x54 (0x15*4): interface D
    // +0x58 (0x16*4): interface E
    this->interfaceVtableA = (void *)&PTR_LAB_00e393f8;
    this->interfaceVtableB = (void *)&PTR_LAB_00e39408;
    this->interfaceVtableC = (void *)&PTR_LAB_00e3940c;
    this->interfaceVtableD = (void *)&PTR_LAB_00e39410;
    this->interfaceVtableE = (void *)&PTR_LAB_00e39470;

    // Call engine startup (e.g., initializes subsystems, registers event handlers)
    FUN_00561f10();

    // Zero out fields at offset +0x260 (0x98*4) and +0x180 (0x60*4)
    this->field_0x98 = 0;
    this->field_0x60 = 0;

    // Allocate a 20-byte helper/callback object (e.g., for input handling or event dispatch)
    helperObj = FUN_009c8e50(0x14);
    if (helperObj != NULL) {
        // Set up vtable pointers for the helper object (3 interfaces + back pointer + zero)
        helperObj->vtable1 = (void *)&PTR_LAB_00e3926c;
        helperObj->vtable2 = (void *)&PTR_LAB_00e39280;
        helperObj->vtable3 = (void *)&PTR_LAB_00e39294;
        helperObj->backPointer = this;  // pointer back to main Player object
        helperObj->field_0x10 = 0;     // initialized to zero
    }
    // Store helper object at offset +0x264 (0x99*4)
    this->helperObj = helperObj;

    // If global configuration flag is set, copy or initialize something from global data
    if (DAT_0120e93c != 0) {
        FUN_00407e60(&this->interfaceVtableA, &DAT_0120e93c);
    }

    return this;
}