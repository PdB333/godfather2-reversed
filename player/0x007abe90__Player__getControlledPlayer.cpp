// FUNC_NAME: Player::getControlledPlayer
// Reconstructed from Ghidra decompilation at 0x007abe90
// Returns a pointer to the currently controlled player object if a specific flag is set.
// this: Player object at param_1
// Uses offset 0x58 to access PlayerManager, checks flag at manager+0x8e0 bit 10,
// then retrieves a slot pointer at manager+0x74c and adjusts it back to the owning Player.

int __fastcall Player::getControlledPlayer(Player* this)
{
    // Get the PlayerManager pointer (offset +0x58 from this Player)
    PlayerManager* manager = *(PlayerManager**)((char*)this + 0x58);

    // Check if bit 10 (0x400) is set in the manager's flag field at +0x8e0
    if (((*(uint32_t*)((char*)manager + 0x8e0) >> 10) & 1) != 0)
    {
        // Get a pointer from manager's slot at +0x74c
        char* slotPtr = *(char**)((char*)manager + 0x74c);
        if (slotPtr != 0)
        {
            // Subtract 0x48 to get the containing Player object (slotPtr points into Player at +0x48)
            return (int)(slotPtr - 0x48);
        }
    }
    return 0;
}