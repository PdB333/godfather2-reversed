// FUNC_NAME: EARSObject::constructor
// Function address: 0x005df350
// Reconstructed constructor for base game object (EARS engine)

EARSObject* __thiscall EARSObject::constructor(EARSObject* this, byte doExtraInit) {
    // Set virtual function table pointer to class-specific vtable
    this->vtable = (void*)&PTR_FUN_00e3f2e8; // +0x00

    // Call base class initialization (common setup)
    this->baseInit(); // FUN_004de130

    // If the extra initialization flag is set, perform additional setup (e.g., cleanup or registration)
    if ((doExtraInit & 1) != 0) {
        this->extraInit(); // FUN_009c8eb0
    }

    return this;
}