// FUNC_NAME: GameObject::getUnknownFlag
// Function address: 0x00716780
// Reads a 32-bit field at offset 0x154, shifts right by 13 bits, and masks with 0xFFFFFF01
// Purpose unclear - likely extracting a combined flag/state from a bitfield
uint32_t GameObject::getUnknownFlag() const
{
    // Access the field at this+0x154 (e.g., a union/bitfield for various flags)
    uint32_t field = *(uint32_t*)((uint8_t*)this + 0x154);
    // Shift right by 13 bits to isolate bits 13..31, then mask to retain only bit 0 and bits 8..31
    return (field >> 13) & 0xFFFFFF01;
}