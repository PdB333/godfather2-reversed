//FUNC_NAME: Entity::setActiveFlag
void __thiscall Entity::setActiveFlag(int thisPtr, int conditionParam)
{
    char conditionResult;
    
    conditionResult = checkCondition(conditionParam);
    if (conditionResult != '\0') {
        // Set bit 0x40 (active flag) at offset +0x1d0
        *(uint *)(thisPtr + 0x1d0) = *(uint *)(thisPtr + 0x1d0) | 0x40;
        return;
    }
    // Clear bit 0x40
    *(uint *)(thisPtr + 0x1d0) = *(uint *)(thisPtr + 0x1d0) & 0xffffffbf;
    return;
}