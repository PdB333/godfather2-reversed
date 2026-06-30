// FUNC_NAME: GameSingleton::initialize
void __thiscall GameSingleton::initialize(void)
{
    // this pointer in ESI (unaff_ESI)
    // Set vtable pointer at +0x00
    this->vtable = &vtable_00e3fd80;

    // Clear array starting at +0x04, size 0x240 bytes (9 slots of 0x40 or similar)
    memset(&this->array, 0, 0x240);

    // Set fields at dword offsets 0x91, 0x92, 0x93, 0x94, 0x95, and byte at 0x96
    // These offsets are beyond the memset region (0x04 + 0x240 = 0x244)
    // +0x244 = 0x91*4
    this->field_0x91 = 0;
    this->field_0x92 = 0;
    this->field_0x93 = 0;
    this->field_0x94 = 0;   // +0x250
    this->field_0x95 = 0;   // +0x254
    *(byte *)(&this->field_0x95 + 1) = 0;  // byte at +0x258 (0x96*4)

    // Store this instance in global singleton pointer
    g_singletonInstance = this;
}