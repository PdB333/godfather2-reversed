// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004bf850 — Constructor for an EARS engine object, sets vtable and initializes flags

__thiscall EARSObject::EARSObject()
{
    // Step 1: Call base class constructor (likely EARSBaseObject)
    EARSBaseObject::EARSBaseObject();

    // Step 2: Set vtable pointer (first 4 bytes of object)
    vfptr = (void**)&PTR_LAB_00e35ea8;

    // Step 3: Initialize object-specific fields (offsets in dwords from this)
    // Offset 0x8a (byte 0x228): set to -1 (e.g., timer/ID)
    *((int32_t*)this + 0x8a) = -1;
    // Offset 0x8b (byte 0x22C): clear to 0
    *((int32_t*)this + 0x8b) = 0;
    // Offset 0x2e (byte 0xB8): OR bit 2 (0x04) into a flags field
    *((uint32_t*)this + 0x2e) |= 4;
    // Offset 0x3d (byte 0xF4): set byte to 1 (boolean active/visible)
    *((uint8_t*)this + 0x3d) = 1;
}