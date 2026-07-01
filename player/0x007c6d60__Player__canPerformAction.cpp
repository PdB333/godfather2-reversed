// FUNC_NAME: Player::canPerformAction
// Function at 0x007c6d60
// Checks if the player is allowed to perform a specific action based on game state, flags, and input.
int __fastcall Player::canPerformAction(int thisPtr)
{
    int isGameActive = FUN_007ab1f0(); // likely checks if the game is in a playable state
    if (isGameActive)
    {
        // Dereference pointer at +0x58 to get a sub-structure, then read flags at offset 0x8e4
        uint flags = *(uint*)(*(int*)(thisPtr + 0x58) + 0x8e4);
        // Condition: bit8 set (0x100), bit9 clear (0x200)
        if (((flags >> 9) & 1) == 0 && ((flags >> 8) & 1) != 0)
        {
            // Check bit0 of byte at +0x128 (some player flag)
            if ((*(byte*)(thisPtr + 0x128) & 1) != 0)
            {
                char inputAllowed = FUN_00701280(); // likely checks if input/action is permitted
                if (inputAllowed != 0)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}