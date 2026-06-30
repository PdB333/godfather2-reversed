// FUNC_NAME: NPC::checkSuccessChance
bool __thiscall NPC::checkSuccessChance(int thisPtr, float threshold) {
    // +0x74: current state (e.g., AIState enum)
    int currentState = *(int*)(thisPtr + 0x74);
    if (currentState != 0 && currentState != 0x48) { // 0x48 likely a specific state (e.g., STATE_COVER)
        float minRand = DAT_00e51bbc; // likely 0.0f
        float scale = DAT_00e44590;   // likely 1.0f / RAND_MAX
        int randomInt = _rand();
        float randomFloat = (float)randomInt * scale + minRand;
        if (threshold <= randomFloat) {
            char extraCheck = FUN_007692f0(); // additional condition (e.g., canAct)
            if (extraCheck == 0) {
                return true;
            }
        }
    }
    return false;
}