// FUNC_NAME: SomeManager::constructor
// Address: 0x009608f0
// Role: Constructor for a singleton manager class (stores global pointer at 0x0113087c)

void __fastcall SomeManager::constructor(SomeManager* this) {
    // Call base class constructor (likely EARS::Framework::Object or similar)
    FUN_005bf9b0();

    // Set vtable pointer at offset 0x00
    this->vtable = &PTR_FUN_00d8d370;

    // Set field at offset 0x10 (param_1[4]) to a function table or data
    this->field_0x10 = &PTR_LAB_00d8d348;

    // Set field at offset 0x4C (param_1[0x13]) to a data pointer
    this->field_0x4C = &PTR_LAB_00d8d340;

    // Overwrite same field? Possibly a bug in decompilation or two different fields at same offset.
    // In the original assembly, this might be param_1[0x14] or similar.
    this->field_0x4C = &PTR_LAB_00d8d344;

    // Store this pointer in global singleton
    _DAT_0113087c = this;
}