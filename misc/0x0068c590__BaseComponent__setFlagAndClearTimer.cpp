// FUNC_NAME: BaseComponent::setFlagAndClearTimer
void __thiscall BaseComponent::setFlagAndClearTimer(int thisPtr, byte flagValue)
{
    // Set a byte flag at offset +0x15 (likely m_activeFlag or m_stateFlag)
    *(byte *)(thisPtr + 0x15) = flagValue;
    // Clear a dword at offset +0x18 (likely m_cooldownTimer or m_counter)
    *(uint *)(thisPtr + 0x18) = 0;
}