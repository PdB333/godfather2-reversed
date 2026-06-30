// FUNC_NAME: Player::getActionState
// Address: 0x005dd8a0
// Reconstructed C++ method for The Godfather 2 (EARS engine)
// This function retrieves two action state values based on input flags and allowed actions mask.

// Constants defined elsewhere (likely in global data section)
extern const uint kInputMask;          // DAT_00f15b80
extern const uint kStateFlagMask;      // DAT_00f15b78 | DAT_00f15b7c (combined)
extern const uint kSpecialFlagMask;    // DAT_012056c0

// Offset within Player object
#define OFFSET_ALLOWED_INPUTS 700      // 0x2BC
#define OFFSET_DEFAULT_STATE1 0x284
#define OFFSET_DEFAULT_STATE2 0x288
#define OFFSET_ALT_STATE1     0x28C
#define OFFSET_ALT_STATE2     0x290

void __thiscall Player::getActionState(uint inputFlags, uint* outPrimary, uint* outSecondary)
{
    // Apply input mask
    uint maskedInput = kInputMask & inputFlags;

    // Extract the combined state flags
    uint combinedFlags = kStateFlagMask & maskedInput;

    // Determine whether to use alternative state values
    bool useAlternative = false;
    if (combinedFlags != kStateFlagMask)
    {
        bool hasSpecialFlag = (kSpecialFlagMask & maskedInput) != 0;
        bool hasSomeFlagsButBlocked = (combinedFlags != 0) && ((*(uint*)(this + OFFSET_ALLOWED_INPUTS) & maskedInput) == 0);
        if (hasSpecialFlag || hasSomeFlagsButBlocked)
        {
            useAlternative = true;
        }
    }

    if (useAlternative)
    {
        // Alternative state pair: +0x28C and +0x290
        *outPrimary   = *(uint*)(this + OFFSET_ALT_STATE1);
        *outSecondary = *(uint*)(this + OFFSET_ALT_STATE2);
    }
    else
    {
        // Default state pair: +0x284 and +0x288
        *outPrimary   = *(uint*)(this + OFFSET_DEFAULT_STATE1);
        *outSecondary = *(uint*)(this + OFFSET_DEFAULT_STATE2);
    }
}