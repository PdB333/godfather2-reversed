// FUNC_NAME: TNLConnection::constructor
undefined4 * __thiscall TNLConnection::constructor(TNLConnection *this, int createSocketFlag)
{
    undefined4 socketHandle;

    // If createSocketFlag is nonzero, create a network socket
    if (createSocketFlag == 0) {
        socketHandle = 0;
    } else {
        socketHandle = FUN_00481610(); // Creates socket, returns handle
    }

    // Common initialization (memory? debug?)
    FUN_0064d390(1, 1);

    // Set base class vtable
    this->vtable = (void *)&PTR_LAB_00e317dc;

    // +0x18: unknown flag (offset 0x18 = 6*4)
    this->field_0x18 = 0;

    // Initialize connection with socket handle
    FUN_00454a10(socketHandle);

    // +0x24: set to 1 (likely active/connected flag, offset 0x24 = 9*4)
    this->field_0x24 = 1;

    // Override vtable to derived class vtable
    this->vtable = (void *)&PTR_LAB_00d61534;

    // +0x28: pointer to interface vtable (offset 0x28 = 10*4)
    this->interfaceVtable = (void *)&PTR_LAB_00d614f0;

    // +0x30: callback function pointer (offset 0x30 = 12*4)
    this->callback = &LAB_0070b010;

    // +0x34: unknown (offset 0x34 = 13*4)
    this->field_0x34 = 0;

    // +0x14: pointer to subobject at offset 0x28 (offset 0x14 = 5*4)
    this->subobjectPtr = (int *)((char *)this + 0x28);

    return this;
}