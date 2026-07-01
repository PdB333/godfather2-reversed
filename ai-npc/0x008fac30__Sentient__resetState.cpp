// FUNC_NAME: Sentient::resetState
void __thiscall Sentient::resetState(void *this, uint msgId, void *msgData)
{
    uint *puVar1;
    int *piVar2;
    String tempStr; // stack-based temporary string buffer

    // Initialize temp string with a global constant and then perform string release/clear
    tempStr = *DAT_0112fe88;
    tempStr.length = 0;
    tempStr.capacity = 0;
    stringRelease(&tempStr, 0);

    // Reset animation state
    m_animState = 0;

    // Cancel any pending timer using stored handle (negated to cancel)
    cancelTimer(-(int)m_timerHandle);
    m_timerHandle = 0;

    // Set bit 3 in flags (e.g., indicates "reset in progress")
    m_flags |= 8;

    // Clear action queue / AI state
    clearActionQueue(0);

    // Notify observers (or handle message)
    notifyObservers(msgId, msgData);

    // Reset scripting state
    resetScripting();

    // Clear certain timeout or counter
    m_unknownTimeout = 0;

    // Clear bits in state flags (mask 0xfffffabd: ~0x545? actually clears specific bits)
    m_stateFlags &= 0xfffffabd;

    // If there is an animation controller, clear a flag at offset 0x249c
    if (m_animController != 0) {
        puVar1 = (uint *)(m_animController + 0x249c);
        *puVar1 &= 0xfffbffff; // clear bit 14? (0x40000)
    }

    // Clear the name string field
    tempStr = m_nameString;
    tempStr.length = 0;
    tempStr.capacity = 0;
    stringRelease(&tempStr, 0);

    // Reset another global constant string reference
    tempStr = *DAT_0112fea8;
    tempStr.length = 0;
    tempStr.capacity = 0;
    stringRelease(&tempStr, 0);

    // Reset timers
    m_damageTimer1 = 0;
    m_damageTimer2 = 0;
    m_scriptState = 0;

    // If there is a sub-component, delete it and nullify pointer
    piVar2 = &m_subComponent;
    if (*piVar2 != 0) {
        deleteComponent(piVar2);
        *piVar2 = 0;
    }

    // Restore default values from globals
    m_defaultSpeed = *DAT_00d812a8;
    m_defaultReaction = *DAT_01205228;

    return;
}