// FUNC_NAME: Player::getItemFromBitmask
// address: 0x005dd910
// Returns a pointer to an item (or handle) based on an input bitmask and global game flags.
// Uses global bitmasks: g_itemFlags1 (DAT_00f15b80), g_itemFlags2 (DAT_00f15b78), g_itemFlags3 (DAT_00f15b7c), g_specialFlag (DAT_012056c0)
// this + 0x2BC (700) is a bitfield of owned/equipped items.
// returns this+0x254 or this+0x294 depending on conditions.

int* Player::getItemFromBitmask(uint bitmask)
{
    uint localBitmask = g_itemFlags1 & bitmask;
    uint combinedFlags = g_itemFlags2 | g_itemFlags3;
    uint uVar1 = combinedFlags & localBitmask;

    if (uVar1 != combinedFlags
        && (g_specialFlag & localBitmask) != 0
        || (uVar1 != 0 && (*(uint *)(this + 0x2BC) & localBitmask) == 0))
    {
        return *(int **)(this + 0x294);
    }
    return *(int **)(this + 0x254);
}