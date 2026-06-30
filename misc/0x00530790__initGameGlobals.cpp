// FUNC_NAME: initGameGlobals
// This function initializes a global data structure at 0x01219940.
// It sets the vtable pointer, zeros many fields, and sets one field from a ROM constant.
// Called during startup to prepare the game globals.
void initGameGlobals(void)
{
    // Call base initialization (likely memory setup or parent class init)
    FUN_006126d0();

    // Global structure at 0x01219940 (size unknown, but offsets indicate >0xD4 bytes)
    // Set vtable pointer (first field, offset 0x00)
    *(void**)0x01219940 = (void*)0x00e38498; // vtable or function table

    // Zero fields at various offsets (likely flags, counters, pointers)
    *(uint32_t*)0x012199e4 = 0; // offset 0xA4
    *(uint32_t*)0x012199e8 = 0; // offset 0xA8
    *(uint32_t*)0x012199f0 = 0; // offset 0xB0
    *(uint32_t*)0x012199f4 = 0; // offset 0xB4
    *(uint32_t*)0x012199f8 = 0; // offset 0xB8
    *(uint32_t*)0x012199fc = 0; // offset 0xBC
    *(uint32_t*)0x01219a00 = 0; // offset 0xC0
    *(uint32_t*)0x01219a04 = 0; // offset 0xC4
    *(uint32_t*)0x01219a08 = 0; // offset 0xC8
    *(uint32_t*)0x01219a10 = 0; // offset 0xD0
    *(uint32_t*)0x01219a14 = 0; // offset 0xD4
    *(uint32_t*)0x01219a48 = 0; // offset 0x108

    // Set field at offset 0xCC from a ROM constant (DAT_00e2b1a4)
    *(uint32_t*)0x01219a0c = DAT_00e2b1a4; // offset 0xCC, likely a configuration value

    // Return pointer to the structure (though not used here, original returns it)
    // return (undefined4*)0x01219940;
}