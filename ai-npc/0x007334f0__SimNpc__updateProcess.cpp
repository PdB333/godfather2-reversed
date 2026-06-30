// FUNC_NAME: SimNpc::updateProcess
void __thiscall SimNpc::updateProcess(void *this, int eventId) {
  int state;
  int iVar1;
  byte eventFlag;
  byte eventBuffer[16];
  byte local_c;
  int local_8[2];

  eventQueue->pop(eventId);
  if (m_pPhysics != 0) {
    state = getCurrentState();
    switch(state) {
      case 0:
      case 1:
        stateIdle();
        break;
      case 2:
        stateMove();
        break;
      case 3:
        stateAttack();
    }
    clearPendingEvent(0);
    buildEventContext(eventBuffer, eventId);
    if ((local_c & 1) != 0) {
      dispatchEvent(m_pPhysics, eventBuffer);
      if ((m_nFlags >> 0x14 & 1) != 0) {
        dispatchEvent(0xbdee6638, eventBuffer); // hash for local player
      }
      if (isLocalPlayer(m_pPlayerData)) {
        handleLocalEvent(eventBuffer);
      }
    }
    if (local_8[0] != 0) {
      freeEventContext(local_8);
    }
  }
  if (((m_nFlags >> 8 & 1) != 0) && (m_pVehicle != 0)) {
    updateVehiclePhysics(this - 0x394, m_pVehicle);
  }
  if ((m_nAnimationState != 0) && (m_nAnimationState != 0x48)) {
    updateAnimation(this - 0x394);
  }
  if (m_bPendingAction != '\0') {
    clearPendingActionQueue();
    m_bPendingAction = 0;
  }
  iVar1 = m_pStreamResource;
  if (iVar1 != 0) {
    releaseStreamResource();
    destroyResource(iVar1);
    m_pStreamResource = 0;
  }
  return;
}