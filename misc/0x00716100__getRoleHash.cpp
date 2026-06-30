// FUNC_NAME: getRoleHash
#include <cstdint>

// Returns a 32-bit hash or identifier based on entity flags and global state.
// Likely used to determine faction/side for AI or UI display.
// param1: pointer to an entity object, with a pointer at +0x18 to a data block
//         containing flags at offset +0x8e0 (bit 1 tested).
// FUN_00800b60() appears to return the current global role/context (1-4).
uint32_t __fastcall getRoleHash(int entity)
{
    uint32_t globalRole = FUN_00800b60(); // Returns 1 for player, 2-4 for others?
    uint32_t flags = *(uint32_t*)(*(int*)(entity + 0x18) + 0x8e0); // +0x18 pointer to data, +0x8e0 flags

    if ((flags & 2) == 0) // Bit 1 clear: entity is not special (e.g., non-player)
    {
        if (globalRole == 1)
            return 0x15d2906b; // Hash for player in first role
        if (globalRole >= 2 && globalRole <= 4) // Roles 2-4 (family members? enemies?)
            return 0xf60ba72a;
    }
    else // Bit 1 set: entity is special (e.g., player, boss, etc.)
    {
        if (globalRole == 1)
            return 0xd12590c2; // Hash for self/player role 1
        if (globalRole >= 2 && globalRole <= 4)
            return 0xd86dde49;
    }
    return 0; // Default: no hash
}