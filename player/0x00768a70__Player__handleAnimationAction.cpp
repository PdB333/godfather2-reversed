// FUNC_NAME: Player::handleAnimationAction

// Reconstructed from Ghidra decompile at 0x00768a70
// Handles specific animation actions (IDs 0x23, 0x24) and delegates others to default handler.
int __thiscall Player::handleAnimationAction(int param2, float deltaTime, int param4, int actionId, int param6)
{
    // Offset 0x5c from 'this' -> pointer to animation substate/component
    int* animationSubstate = *(int**)(this + 0x5c);

    if (actionId == 0x23) {
        // Check a system condition (e.g., debug enabled, game state)
        int systemResult = FUN_00800b60();
        if (systemResult != 0) {
            int* vtable = *(int**)this; // vtable pointer of this
            // Create animation handle/command: parameters: loop=1, reset=1, unknown=0, animData from substate+0x1dbc, speed=1.0f
            int animHandle = FUN_00715f30(1, 1, 0, *(int*)(animationSubstate + 0x1dbc), 1.0f);
            // Call virtual function at vtable offset 0x2c (likely setActiveAnimation or playAnimation)
            char result = ((char (__thiscall*)(void*, int))((int)vtable + 0x2c))(this, animHandle);
            // Store result at offset 0x70 from 'this' (e.g., animation played flag)
            *(char*)((int)this + 0x70) = result;
        }
    }
    else if (actionId == 0x24) {
        // Check a large offset: substate+0x24cc (probably a pointer to some data, e.g., effect/impact)
        int* impactData = *(int**)(animationSubstate + 0x24cc);
        if (impactData != 0) {
            int adjustedPtr = (int)impactData - 0x48; // Adjust pointer to sub-data
            if (adjustedPtr != 0) {
                // Apply some force/effect scaled by global multiplier and deltaTime
                FUN_00470230(adjustedPtr, deltaTime * DAT_00d636b8, 0);
                return 1;
            }
        }
    }
    else {
        // Default handler for other action IDs
        return FUN_0073e610(param2, deltaTime, param4, actionId, param6);
    }
    return 1;
}