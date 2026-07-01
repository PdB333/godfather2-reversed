// FUNC_NAME: GameManager::GameManager (constructor)
// Address: 0x00975c60
// Reconstructed constructor for GameManager singleton. Initializes state and stores global pointer.

__thiscall GameManager::GameManager(void)
{
    // Call base class constructor (likely EARSObject or similar)
    EARSObject::EARSObject();

    // Set vtable for this class (probably derived from multiple bases)
    this->vfptr[0x13] = &GameManager_vtable_00e2f19c;  // +0x4C
    this->field_0x54 = 0;                                 // +0x54 (offset param_1[0x15]? Actually param_1[0x14]=1, then param_1[0x15]=0? Wait careful: param_1[0x13]=vtable; param_1[0x14]=1; param_1[0x15]=0; param_1[0x16]=&some_ptr;)
    // From decomp: param_1[0x13] = &PTR_FUN_00e2f19c;
    // param_1[0x15] = 0;
    // puVar1 = param_1 + 0x13;   // puVar1 points to offset 0x4C
    // param_1[0x14] = 1;
    // param_1[0x16] = &PTR_LAB_00d8f800;
    // DAT_01130598 = param_1;
    // *param_1 = &PTR_FUN_00d8f840; // first vtable at +0x00
    // param_1[4] = &PTR_LAB_00d8f818; // offset 0x10
    // *puVar1 = &PTR_LAB_00d8f808;   // puVar1[0] = offset 0x4C -> now changed to another vtable?
    // param_1[0x16] = &PTR_LAB_00d8f804; // offset 0x58 (since param_1[0x16] is at +0x58)
    // param_1[0x17] = 1; // offset 0x5C
    // ....

    // Reordering assignments to match offsets (assuming 4-byte fields)
    this->baseVtable = &GameManager_base_vtable_00d8f840;   // +0x00
    this->field_0x10 = &GameManager_somePtr_00d8f818;       // +0x10 (param_1[4])
    this->field_0x4C = &GameManager_anotherVtable_00e2f19c; // +0x4C
    this->field_0x50 = 1;                                   // +0x50 (param_1[0x14])
    this->field_0x54 = 0;                                   // +0x54 (param_1[0x15])
    this->field_0x58 = &GameManager_ptr_00d8f800;           // +0x58 (param_1[0x16] initial)
    // Update vtable pointers to final values
    this->field_0x4C = &GameManager_vtable2_00d8f808;      // overwrite +0x4C
    this->field_0x58 = &GameManager_vtable3_00d8f804;      // overwrite +0x58
    this->field_0x5C = 1;                                   // +0x5C (param_1[0x17])
    this->field_0x60 = 0;                                   // +0x60 (param_1[0x18])
    this->field_0x64 = 0;                                   // +0x64 (param_1[0x19])
    this->field_0x68 = 1;                                   // +0x68 (*(undefined1*)(param_1+0x1a)) note: byte assignment, but we'll assume it's bool/int
    this->field_0x6C = 6;                                   // +0x6C (param_1[0x1b])
    this->field_0x70 = 0;                                   // +0x70 (param_1[0x1c])
    this->field_0x78 = 2;                                   // +0x78 (param_1[0x1e])
    this->field_0x7C = -1;                                  // +0x7C (param_1[0x1f])
    *(uint8_t*)(this + 0x80) = 0;                           // +0x80 byte (param_1+0x20)
    *(uint8_t*)(this + 0x81) = 0;                           // +0x81
    *(uint8_t*)(this + 0x82) = 0;                           // +0x82
    *(uint8_t*)(this + 0x83) = 1;                           // +0x83

    // Store global singleton pointer (likely used by other systems)
    g_pGameManager = this;   // DAT_01130598

    // Optionally copy default configuration data if present
    if (g_DefaultConfig1 != 0) {
        memcpy(&this->field_0x4C, &g_DefaultConfig1, 0x8000);  // FUN_00408900
    }
    if (g_DefaultConfig2 != 0) {
        memcpy(&this->field_0x4C, &g_DefaultConfig2, 0x8000);
    }

    return this;
}