// FUNC_NAME: Settings::constructor
void __fastcall Settings::constructor(Settings *this)
{
    // +0x00: vtable for first base class (likely something like Object)
    this->vtable0 = &Settings_vtable_base0; // PTR_FUN_00d730f4
    // +0x04: vtable for second base class (maybe Interface)
    this->vtable1 = &Settings_vtable_base1; // PTR_LAB_00d730f0

    // Store global pointer to this singleton
    g_Settings = this; // DAT_011298d0

    // Initialize various settings fields
    // Default float value from global (likely 1.0f or 0.0f)
    float defaultFloat = g_DefaultFloat; // _DAT_00d5780c

    // +0x20: some float field
    this->field20 = defaultFloat;
    // +0x24: another float field
    this->field24 = defaultFloat;

    // +0x38: boolean or integer flag
    this->field38 = 1;

    // Clear several fields
    this->field08 = 0;
    this->field0C = 0;
    this->field10 = defaultFloat;
    this->field14 = defaultFloat;
    this->field30 = 0;
    this->field34 = 0;
    this->field18 = 0;
    this->field1C = 0;
    this->field3C = 0;

    // First color block (bytes at +0x28 to +0x2F)
    // RGBA? All channels set to 255 (0xFF)
    this->color1_r = 0xFF;    // +0x28
    this->color1_g = 0xFF;    // +0x29
    this->color1_b = 0xFF;    // +0x2A
    this->color1_a = 0xFF;    // +0x2B
    this->padding1_0 = 0;     // +0x2C
    this->padding1_1 = 0;     // +0x2D
    this->padding1_2 = 0;     // +0x2E
    this->color1_extra = 0xFF; // +0x2F

    // More fields (+0x40 onward)
    this->field50 = 0;
    this->field54 = 0;
    this->field58 = defaultFloat;
    this->field5C = defaultFloat;
    this->field70 = 1;
    this->field74 = 0;
    this->field40 = 0;
    this->field44 = 0;
    this->field48 = defaultFloat;
    this->field4C = defaultFloat;

    // Second color block (bytes at +0x60 to +0x67)
    this->color2_r = 0xFF;    // +0x60
    this->color2_g = 0xFF;    // +0x61
    this->color2_b = 0xFF;    // +0x62
    this->color2_a = 0xFF;    // +0x63
    this->padding2_0 = 0;     // +0x64
    this->padding2_1 = 0;     // +0x65
    this->padding2_2 = 0;     // +0x66
    this->color2_extra = 0xFF; // +0x67

    // Final fields
    this->field68 = 0;
    this->field6C = 0;
    this->field78 = 0;
    this->field7C = 0;
}