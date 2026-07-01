// FUNC_NAME: Entity::conditionalToggleFlag
void __thiscall Entity::conditionalToggleFlag(void* this_ptr, char inputState)
{
    // +0x5E3: currentFlag (byte/bool)
    char* currentFlag = (char*)((uintptr_t)this_ptr + 0x5E3);
    // +0x5EC: timer or associated value (uint32)
    uint32_t* timerRef = (uint32_t*)((uintptr_t)this_ptr + 0x5EC);

    // Only toggle if the current state matches the input
    if (*currentFlag == inputState)
    {
        // Set flag to opposite of input (invert)
        *currentFlag = (inputState == '\0') ? 1 : 0;
        // Reset the timer/cooldown to the global constant
        *timerRef = DAT_01205220;
    }
}