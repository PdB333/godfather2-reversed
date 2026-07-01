// FUNC_NAME: SmallStruct::reset
void __fastcall SmallStruct::reset()
// Initializes the structure to default state: first 16 bytes zero, then short zero, then active flag 0xFF, then another flag zero.
{
    *(uint32_t *)this = 0;                   // +0x00
    *(uint32_t *)((uint8_t *)this + 4) = 0;  // +0x04
    *(uint32_t *)((uint8_t *)this + 8) = 0;  // +0x08
    *(uint32_t *)((uint8_t *)this + 0xC) = 0;// +0x0C
    *(uint16_t *)((uint8_t *)this + 0x10) = 0;// +0x10
    *(uint8_t *)((uint8_t *)this + 0x12) = 0xFF;// +0x12 (active flag, default true)
    *(uint8_t *)((uint8_t *)this + 0x13) = 0;   // +0x13 (another flag)
}