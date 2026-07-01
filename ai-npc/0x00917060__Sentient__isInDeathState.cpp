// FUNC_NAME: Sentient::isInDeathState
// Function address: 0x00917060
// Checks if the current state (at +0xB8) is one of the death/downed states (0x12-0x18)
bool __thiscall Sentient::isInDeathState(Sentient* this)
{
    int state = *(int*)(this + 0xB8); // +0xB8: current state enum (e.g., SentientState)

    // State values 0x12 through 0x18 represent various death/unconscious states
    // 0x12 = SENTIENT_DEAD, 0x13 = SENTIENT_DYING, 0x14 = SENTIENT_UNCONSCIOUS,
    // 0x15-0x18 are additional death-related states (e.g., ragdoll, knockback)
    if ((state != 0x12) && (state != 0x13) && (state != 0x14) &&
        (state != 0x15) && (state != 0x16) && (state != 0x17) && (state != 0x18))
    {
        return false;
    }
    return true;
}