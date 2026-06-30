// FUNC_NAME: EARSObject::EARSObject
undefined4 * __thiscall EARSObject::EARSObject(undefined4 *this, undefined4 initParam)
{
    // Call base constructor (FUN_004795d0) with the initialization parameter
    FUN_004795d0(initParam);

    // Set main vtable pointer (class specific)
    *this = &PTR_FUN_00e33018;

    // Set second vtable pointer at offset +0x3C (15 words) – likely interface or base class
    this[0xf] = &PTR_LAB_00e33034;

    // Set third vtable pointer at offset +0x48 (18 words) – another interface
    this[0x12] = &PTR_LAB_00e33044;

    // Zero out fields at offset +0x8C (35 words) and +0x90 (36 words)
    this[0x23] = 0;
    this[0x24] = 0;

    return this;
}