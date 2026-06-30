// FUNC_NAME: NPC::checkActionChance
bool __thiscall NPC::checkActionChance(int thisObj, float chanceThreshold)
{
    float randBias;   // fVar1 from DAT_00e51bb8, a global bias constant
    int randInt;      // result of _rand()
    float randVal;    // computed random value
    char condition;   // result of sub-function call

    // Check if the action state at +0x74 is valid (non-zero and not a specific state 0x48 = 72)
    if (*(int *)(thisObj + 0x74) == 0 || *(int *)(thisObj + 0x74) == 0x48) {
        return false;
    }

    randInt = _rand();
    // Combine global constants: bias (DAT_00e51bb8) and scale (DAT_00e44590) to produce a random threshold
    randVal = (float)randInt * DAT_00e44590 + DAT_00e51bb8;

    // If the chance threshold is not met, return false
    if (chanceThreshold > randVal) {
        return false;
    }

    // Additional condition check: if the sub-function returns false, then this action is allowed
    condition = FUN_007692f0();   // Likely checks if some blocking condition is active
    if (condition == '\0') {
        return true;
    }

    return false;
}