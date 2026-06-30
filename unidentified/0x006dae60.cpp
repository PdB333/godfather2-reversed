// FUN_NAME: DefaultParameters::DefaultParameters
void __thiscall DefaultParameters::DefaultParameters(DefaultParameters *this)
{
    // Set vtable pointer
    *(void **)this = (void *)&PTR_FUN_00d5f630;

    // Initialize first block (indices 0-3)
    this->field_0x0c = 0xff; // param_1[3] initially 0xff
    this->field_0x04 = 0;    // param_1[1]
    *(uint8_t *)(&this->field_0x08) = 0; // param_1[2] as byte

    // Load global default values
    float defaultFloat1 = *(float *)&DAT_00d5780c; // _DAT_00d5780c
    float defaultFloat2 = *(float *)&DAT_00d5e288; // _DAT_00d5e288 (maybe min)
    float defaultFloat3 = *(float *)&DAT_00d5efd0; // _DAT_00d5efd0 (maybe max)
    float defaultFloat4 = *(float *)&DAT_00e446dc; // _DAT_00e446dc (maybe other)

    // First block (offsets 0x14-0x1e) - 11 floats
    this->block1_0x14 = defaultFloat2; // param_1[0x14]
    this->block1_0x15 = defaultFloat3; // param_1[0x15]
    this->block1_0x16 = defaultFloat2; // param_1[0x16]
    this->block1_0x17 = defaultFloat3; // param_1[0x17]
    this->block1_0x18 = defaultFloat1; // param_1[0x18]
    this->block1_0x19 = defaultFloat2; // param_1[0x19]
    this->block1_0x1a = defaultFloat4; // param_1[0x1a]
    this->block1_0x1b = defaultFloat1; // param_1[0x1b]
    this->block1_0x1c = defaultFloat1; // param_1[0x1c]
    this->block1_0x1d = *(float *)&DAT_00d5f5f0; // param_1[0x1d] - additional global
    this->block1_0x1e = *(float *)&DAT_00d5f5f4; // param_1[0x1e] - additional global

    // Second block (offsets 0x2d-0x35) - 9 floats
    this->block2_0x2d = defaultFloat2; // param_1[0x2d]
    this->block2_0x2e = defaultFloat3; // param_1[0x2e]
    this->block2_0x2f = defaultFloat2; // param_1[0x2f]
    this->block2_0x30 = defaultFloat3; // param_1[0x30]
    this->block2_0x31 = defaultFloat1; // param_1[0x31]
    this->block2_0x32 = defaultFloat2; // param_1[0x32]
    this->block2_0x33 = defaultFloat4; // param_1[0x33]
    this->block2_0x34 = defaultFloat1; // param_1[0x34]
    this->block2_0x35 = defaultFloat1; // param_1[0x35]

    // Zero out range 0x36-0x3b (6 words)
    for (int i = 0x36; i <= 0x3b; ++i)
        ((uint32_t *)this)[i] = 0;

    // Reset field_0x3c to 0 (but already zeroed)
    this->field_0x3c = 0;

    // Third sub-block: byte at +0x40, two floats at +0x41, +0x42, zeroed 0x44-0x4b
    *(uint8_t *)((uint8_t *)this + 0x40) = 0;
    this->subBlock3_0x41 = defaultFloat2;
    this->subBlock3_0x42 = defaultFloat3;
    for (int i = 0x44; i <= 0x4b; ++i)
        ((uint32_t *)this)[i] = 0;

    // Fourth sub-block: byte at +0x4c, two floats at +0x4d, +0x4e, zeroed 0x50-0x57
    *(uint8_t *)((uint8_t *)this + 0x4c) = 0;
    this->subBlock4_0x4d = defaultFloat2;
    this->subBlock4_0x4e = defaultFloat3;
    for (int i = 0x50; i <= 0x57; ++i)
        ((uint32_t *)this)[i] = 0;

    // Fifth sub-block: byte at +0x58, two floats at +0x59, +0x5a, zeroed 0x5c-0x63
    *(uint8_t *)((uint8_t *)this + 0x58) = 0;
    this->subBlock5_0x59 = defaultFloat2;
    this->subBlock5_0x5a = defaultFloat3;
    for (int i = 0x5c; i <= 0x63; ++i)
        ((uint32_t *)this)[i] = 0;

    // Sixth block: byte at +0x68 set to 1, zeroed 0x69-0x6c, then field_0x0c set to 0x100
    *(uint8_t *)((uint8_t *)this + 0x68) = 1;
    for (int i = 0x69; i <= 0x6c; ++i)
        ((uint32_t *)this)[i] = 0;

    this->field_0x0c = 0x100; // Override initial value
}