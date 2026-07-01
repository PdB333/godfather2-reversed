// FUNC_NAME: Character::evaluateStateCondition
// Address: 0x00963fd0
// Purpose: Checks the current state (stored at +0xDC) against a set of specific states.
// If the state is one of {0, 2, 3, 5, 6, 7, 8, 9, 0xB},
// returns (globalGameManager->someFlag == 0) as a bool.
// Otherwise returns the state with its low byte cleared (e.g., grouping by high bits).

uint __fastcall Character::evaluateStateCondition(Character* this) {
    uint currentState = *(uint*)((int)this + 0xDC);  // +0xDC: current character state enum

    if ((((((currentState != 5) && (currentState != 7)) && (currentState != 8)) &&
          ((currentState != 0 && (currentState != 9)))) &&
         ((currentState != 2 && ((currentState != 3 && (currentState != 6)))))) &&
        (currentState != 0xB)) {
        // Not one of the special states – return the state with the detail byte masked off
        return currentState & 0xFFFFFF00;
    }

    // In one of the special states – return whether a global condition is active
    // DAT_01129828 is a global pointer, assumed to be a game manager/state object
    uint* globalGameManager = (uint*)DAT_01129828;  // static global address
    return (uint)(*(int*)(globalGameManager + 0x3) == 0);  // +0xC: some flag, e.g. "isPaused" or "isProcessing"
}