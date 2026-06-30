// FUNC_NAME: ActionController::handleAction
// Function at 0x0073e300: handles various action commands/checks for an entity.
// Uses member offsets: +0x38 flags, +0x3c mask, +0x5c owner entity ptr, +0x60 timer, +0x68 action state.

typedef unsigned int uint;

// External functions (implementations elsewhere)
extern bool isInCutscene();                          // 0x007f47a0
extern float getPlayerDistance();                    // 0x006252c0
extern int getRandomInt();                          // 0x00471610
extern float computeRandomOffset(int, int);         // 0x0045c470
extern uint getMovementFlags();                     // 0x006252d0
extern bool baseHandler(uint, uint, int, uint);     // 0x004ac640 (default case)

bool ActionController::handleAction(uint param2, uint param3, int actionType, uint param5)
{
    bool result = false;

    switch (actionType)
    {
    case 10: // Check if action allowed by flags or timer active
        if ((*(uint*)(this + 0x38) & *(uint*)(this + 0x3c)) != 0 || *(int*)(this + 0x60) != 0)
            return true;
        break;

    case 11: // Check owner's state at offset 0x2004
    {
        int ownerState = *(int*)(*(int*)(this + 0x5c) + 0x2004);
        if (ownerState == 0)
            return false;
        return ownerState != 0x48;
    }

    case 12: // Skip if cutscene is playing
        if (isInCutscene())
            return true;
        break;

    case 13: // Action state is idle or specific value 0x48
        if (*(int*)(this + 0x68) == 0)
            return true;
        return *(int*)(this + 0x68) == 0x48;

    case 14: // Check distance with random offset (noise)
    {
        int actionState = *(int*)(this + 0x68);
        if (actionState == 0 || actionState == 0x48)
            return true;

        float dist = getPlayerDistance();               // e.g., distance to player
        int noiseX = getRandomInt() + 0x30;             // add 0.3 in fixed point
        int noiseZ = getRandomInt() + 0x30;
        float threshold = computeRandomOffset(noiseZ, noiseX); // returns squared threshold
        if (dist * dist < threshold)
            return true;
        break;
    }

    case 15: // Clear a movement flag if not in cutscene
    {
        uint mask = getMovementFlags();
        if ((*(uint*)(this + 0x38) & mask) != 0 && !isInCutscene())
        {
            *(uint*)(this + 0x38) &= ~mask;
            return true;
        }
        break;
    }

    case 16: // Cutscene active plus a specific bit in owner at +0x1b94
        if (isInCutscene() && (*(uint*)(*(int*)(this + 0x5c) + 0x1b94) & (1 << 6)) != 0)
            return true;
        break;

    case 17: // Test and clear bit 8 in owner at +0x1f5c
    {
        uint old = *(uint*)(*(int*)(this + 0x5c) + 0x1f5c);
        *(uint*)(*(int*)(this + 0x5c) + 0x1f5c) = old & ~0x100;
        return (old & 0x100) != 0;
    }

    default:
        result = baseHandler(param2, param3, actionType, param5);
    }

    return result;
}