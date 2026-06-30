// FUNC_NAME: Player::handleGameplayEvent
void __thiscall Player::handleGameplayEvent(void *param_2,undefined4 param_3,int param_4,undefined4 param_5)
{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  
  // Resolve handles and call initialization
  uVar2 = resolveHandle(*(undefined4 *)(this + 0x40));
  someSetup(uVar2);
  
  // Resolve the event source handle and process the event
  uVar2 = resolveHandle(param_2);
  processEvent(uVar2,param_2,param_3,param_4,param_5);
  
  // If the event is not from a remote source (param_4 == 0 means local)
  if (param_4 == 0) {
    // Check if this is the local player (flags: +0xc4 == 1 indicating local, +0xc0 non-zero)
    if ((*(int *)(this + 0xc4) == 1) && (*(int *)(this + 0xc0) != 0)) {
      iVar3 = getLocalPlayerIndex();
      if (iVar3 != 0) {
        iVar3 = getLocalPlayerIndex();
        // 0x637b907 likely a specific event type hash (e.g., "PLAYER_KILLED" or "GENERIC_EVENT")
        if ((iVar3 != 0x637b907) && (param_2 == (void *)0x637b907)) {
          bVar1 = isLocalPlayer();
          if (bVar1 != false) {
            // Send a network event with hash 0x9baf024 (e.g., "PROPAGATE_EVENT" or "MISSION_UPDATE")
            sendNetworkEvent(0x9baf024);
          }
        }
      }
    }
    // Process additional local logic using another handle at +0x38
    processLocalEvent(*(undefined4 *)(this + 0x38));
  }
  
  // Select different state machine based on a flag at +0xfc
  if (*(int *)(this + 0xfc) != 0) {
    handleStateA();
    return;
  }
  handleStateB();
  return;
}