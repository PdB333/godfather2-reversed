// FUNC_NAME: Player::isActionAllowed
// Function address: 0x007c97f0
// Role: Checks if the player is allowed to perform a specific action based on game state and flags.
// Uses global state (FUN_007abe90) and player state flags at offsets +0x8e8 and +0x8e0.
// Also checks a byte at global state +0x1a8 for value 0x05, or a value at player state +0x30c0 not equal to 0x48.

bool __fastcall Player::isActionAllowed(int this) // this = param_1
{
    int globalState;
    int playerState;
    int someValue;
    void* obj;
    char result;

    globalState = getGlobalState(); // FUN_007abe90
    if (((globalState != 0) && (*(char*)(globalState + 0x1a8) == '\x05')) ||
        ((someValue = *(int*)(*(int*)(this + 0x58) + 0x30c0), someValue != 0 && (someValue != 0x48))))
    {
        playerState = *(int*)(this + 0x58); // +0x58: pointer to player state structure
        if (((*(uint*)(playerState + 0x8e8) >> 2 & 1) != 0) || // bit 2 of flags at +0x8e8
            ((*(uint*)(playerState + 0x8e0) >> 9 & 1) != 0))   // bit 9 of flags at +0x8e0
        {
            obj = createObject(0x38); // FUN_00798f50(0x38) - likely allocates or retrieves an object of size 0x38
            result = checkObject(obj); // FUN_0079e920 - returns non-zero if valid
            if (result != 0)
            {
                return true;
            }
        }
    }
    return false;
}