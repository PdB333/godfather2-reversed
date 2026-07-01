// FUNC_NAME: Entity::isFlagSet
// Function at 0x007f8f10: Checks bit 15 of a flags field at offset 0x490.
// Likely a member function of a game object (e.g., Entity, Sentient, Player, NPC).
// Returns true if the bit is set.
bool __thiscall Entity::isFlagSet(void) const {
    // +0x490: flags bitfield
    return (*(uint32_t*)((uint8_t*)this + 0x490) >> 0xF) & 1;
}