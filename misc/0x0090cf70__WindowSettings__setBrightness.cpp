//FUNC_NAME: WindowSettings::setBrightness
void __thiscall WindowSettings::setBrightness(int this, int brightness)
{
    int *ptr;
    int local_c; // value from this+0x2c
    int local_8; // unused, from global
    float local_4; // unused, computed brightness factor

    local_8 = _DAT_00d5780c; // some global constant
    local_c = *(int *)(this + 0x2c); // +0x2c: pointer to display context or settings
    *(int *)(this + 0x38) = brightness; // +0x38: store brightness value
    ptr = (int *)(DAT_01206880 + 0x14); // global pointer to a registration table
    local_4 = (float)brightness * _DAT_00d83544; // brightness multiplier (unused)
    *(void ***)*ptr = &PTR_LAB_00e549f0; // register a vtable or callback
    *ptr = *ptr + 4; // advance to next slot
    FUN_0049c430(&local_c, 0x10, 0x10); // update display context (size 0x10)
    FUN_0069bf90("Window.Bright", brightness); // set console variable
    return;
}