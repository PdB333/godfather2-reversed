// FUNC_NAME: CSACrewComponent::updateState
undefined1 __thiscall CSACrewComponent::updateState(CSACrewComponent* this)
{
  // +0x9088: m_bActive (byte) - indicates if this component needs state update
  if (this->m_bActive != '\0') {
    // +0x9098: m_timeRemaining (int) - default timer value
    // +0x9094: m_state (int) - state index
    // +0x909c: m_timer (int) - secondary timer
    // +0x90a0: m_cooldown (int) - cooldown counter
    // +0x908c: m_counter (int) - general counter
    this->m_timeRemaining = DAT_00e44620;
    this->m_state = 0;
    this->m_timer = DAT_00e2b1a4;
    this->m_cooldown = 0;
    this->m_counter = 0;
    // Internal state transition helper
    CSACrewComponent::updateSubState(this);
    this->m_bActive = '\0';
  }
  return 1;
}