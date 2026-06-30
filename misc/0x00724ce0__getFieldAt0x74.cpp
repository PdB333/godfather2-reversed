// FUNC_NAME: getFieldAt0x74
// Address: 0x00724ce0
// Role: Simple getter returning the value at offset 0x74 from the object's base (likely a pointer or a 4-byte member variable).
// This function is called from 0x00872ff0, and may be part of a larger class hierarchy (e.g., EARS::Entity, NPC, Player, etc.).

// __fastcall convention: first parameter in ecx (param_1 = this)
uint32_t __fastcall getFieldAt0x74(uint32_t thisPtr)
{
    // Offset 0x74: typical location for a pointer to parent/owner/container or a small integer member.
    return *(uint32_t *)(thisPtr + 0x74);
}