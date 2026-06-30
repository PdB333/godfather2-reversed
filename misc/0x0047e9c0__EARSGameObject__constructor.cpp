// FUNC_NAME: EARSGameObject::constructor
EARSGameObject* __thiscall EARSGameObject::constructor(EARSGameObject* this, void* someParam)
{
    // Call base class constructor (likely EARSObject or similar)
    BaseClass::constructor(someParam);

    // VTable pointer for this class (offset 0x00)
    this->vtable = &g_vtable_EARSGameObject;

    // Secondary vtable pointers (offsets 0x3C, 0x48) – likely interface tables
    this->interfaceTable1 = &g_interfaceTable1_EARSGameObject;
    this->interfaceTable2 = &g_interfaceTable2_EARSGameObject;

    // Initialize fields at offsets 0x50, 0x54, 0x56, 0x58
    this->field_0x50 = 0;                        // dword
    *(uint16_t*)((uint8_t*)this + 0x54) = 0;     // word at +0x54
    *(uint16_t*)((uint8_t*)this + 0x56) = 0;     // word at +0x56
    this->field_0x58 = 0;                        // dword at +0x58

    return this;
}