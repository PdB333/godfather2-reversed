// FUNC_NAME: EARSGameObject::EARSGameObject
// Address: 0x00480910
// Role: Constructor for an EARS game object (likely a network packet or entity node)
// Initializes multiple vtable/interface pointers, sentinel debug patterns, and zeros members
void __thiscall EARSGameObject::EARSGameObject(void* this, uint32_t param2)
{
    // Call base class constructor (FUN_0046c590)
    baseClassConstructor(param2);

    // Set vtable pointers for multiple inheritance (offsets in bytes from this)
    *(void**)((uint8_t*)this + 0x50) = &VTABLE_00e32854;   // +0x50: first vtable (later overwritten)
    *(void**)((uint8_t*)this + 0x00) = &VFUNC_00e33404;    // +0x00: primary vtable
    *(void**)((uint8_t*)this + 0x3C) = &VTABLE_00e33420;   // +0x3C: secondary vtable
    *(void**)((uint8_t*)this + 0x48) = &VTABLE_00e33430;   // +0x48: tertiary vtable
    *(void**)((uint8_t*)this + 0x50) = &VTABLE_00e33434;   // +0x50: final vtable (overwrites first)

    // Zero out various members
    *(uint32_t*)((uint8_t*)this + 0x54) = 0;               // +0x54: some pointer
    *(uint16_t*)((uint8_t*)this + 0x58) = 0;               // +0x58: short value
    *(uint16_t*)((uint8_t*)this + 0x5A) = 0;               // +0x5A: another short
    *(uint32_t*)((uint8_t*)this + 0x5C) = 0;               // +0x5C: word
    *(uint16_t*)((uint8_t*)this + 0x60) = 0;               // +0x60: short
    *(uint16_t*)((uint8_t*)this + 0x62) = 0;               // +0x62: short

    // Set debug sentinel values (then immediately cleared below – may be for memory tracking)
    *(uint32_t*)((uint8_t*)this + 0x64) = 0xbadbadba;      // +0x64: sentinel
    *(uint32_t*)((uint8_t*)this + 0x68) = 0xbeefbeef;      // +0x68: sentinel
    *(uint32_t*)((uint8_t*)this + 0x6C) = 0xeac15a55;      // +0x6C: sentinel
    *(uint32_t*)((uint8_t*)this + 0x70) = 0x91100911;      // +0x70: sentinel

    // Zero out flags and remaining sentinels
    *(uint32_t*)((uint8_t*)this + 0x74) = 0;               // +0x74: flag
    *(uint32_t*)((uint8_t*)this + 0x78) = 0;               // +0x78: flag
    *(uint32_t*)((uint8_t*)this + 0x7C) = 0;               // +0x7C: flag
    *(uint32_t*)((uint8_t*)this + 0x80) = 0;               // +0x80: flag
    *(uint8_t*)((uint8_t*)this + 0x84) = 0;                // +0x84: byte

    // Clear the sentinel fields to 0 (final initialization)
    *(uint32_t*)((uint8_t*)this + 0x70) = 0;               // +0x70: cleared
    *(uint32_t*)((uint8_t*)this + 0x6C) = 0;               // +0x6C: cleared
    *(uint32_t*)((uint8_t*)this + 0x68) = 0;               // +0x68: cleared
    *(uint32_t*)((uint8_t*)this + 0x64) = 0;               // +0x64: cleared
}