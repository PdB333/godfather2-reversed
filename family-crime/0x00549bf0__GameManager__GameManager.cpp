// FUNC_NAME: GameManager::GameManager
// Constructor for GameManager class. Initializes vtable, calls base subobject constructor at offset 0x10,
// sets default values to global constant, and zeros out several fields.

// Known offsets:
// +0x00: vtable pointer
// +0x04: subobject? (base class instance)
// +0x10: first field (int/float) set to DAT_00e2b1a4
// +0x24: second field set to same global
// +0x38: third field set to same global
// +0x40: field zeroed (int)
// +0x44: field zeroed
// +0x48: field zeroed
// +0x4C: field zeroed
// +0x10C: field set to 0
// +0x110: field set to 0

__fastcall GameManager::GameManager(GameManager *this)
{
    // Set vtable pointer to the static table for this class
    this->vtable = &PTR_FUN_00e39bc8;

    // Call subobject constructor at offset 0x10 (actual base class instance)
    // Parameters: 0, address of subobject, 0
    subObjectConstructor(0, &this->baseSubObject, 0);

    // Initialize fields at offsets 0x10C and 0x110 to 0
    this->field_0x10C = 0;
    this->field_0x110 = 0;

    // Call a global initializer (possibly seed or config)
    FUN_0045cbe0();

    // Get the global default value (likely a float constant like 1.0f)
    uint32 globalDefault = DAT_00e2b1a4;

    // Set multiple fields to this default value
    this->field_0x10 = globalDefault;   // offset +0x10
    this->field_0x24 = globalDefault;   // offset +0x24
    this->field_0x38 = globalDefault;   // offset +0x38

    // Zero out four consecutive fields at offsets 0x40, 0x44, 0x48, 0x4C
    this->field_0x40 = 0;
    this->field_0x44 = 0;
    this->field_0x48 = 0;
    this->field_0x4C = 0;

    return this;
}