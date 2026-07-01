// FUNC_NAME: MaterialEffect::applyParameters
void __thiscall MaterialEffect::applyParameters(
    void *this,
    float param_2,           // unused? maybe blend factor
    int param_3,             // unused? maybe index
    uint32_t param_4,        // used as bool in setBlendMode
    float param_5,           // unused
    float param_6,           // unused
    uint32_t *param_7)       // pointer to 13 DWORD parameter array
{
    uint32_t savedParam;                 // +0x2010
    uint32_t *paramDest;                 // +0x2024 (start of parameter block)
    int i;

    savedParam = *(uint32_t *)((uint32_t)this + 0x2010);
    paramDest = (uint32_t *)((uint32_t)this + 0x2024);

    // Copy 13 parameters (52 bytes) from external source
    for (i = 0xd; i != 0; i = i - 1) {
        *paramDest = *param_7;
        param_7++;
        paramDest++;
    }

    // Restore saved parameter into offset 0x201c (possibly previous value)
    *(uint32_t *)((uint32_t)this + 0x201c) = savedParam;

    // Apply renderer state with saved parameter and secondary field
    FUN_00422a40(savedParam, *(uint32_t *)((uint32_t)this + 0x2014), 0, 0);

    // Set blend mode using parameter param_4 as flag
    FUN_00422bc0(param_4, 1);

    // Apply texture-related setting from the copied block (offsets 0x2050, 0x204c)
    FUN_00422e80(*(uint32_t *)((uint32_t)this + 0x2050), *(uint32_t *)((uint32_t)this + 0x204c));

    // Apply shader-related setting from the copied block (offsets 0x2044, 0x2048)
    FUN_00422fb0(*(uint32_t *)((uint32_t)this + 0x2044), *(uint32_t *)((uint32_t)this + 0x2048));
}