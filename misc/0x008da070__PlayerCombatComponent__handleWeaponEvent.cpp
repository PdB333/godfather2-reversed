// FUNC_NAME: PlayerCombatComponent::handleWeaponEvent
// Address: 0x008da070
// Role: Processes weapon-related event messages for the player combat component.
// The function dispatches based on message ID (param_2[0]) and handles state transitions,
// weapon virtual calls, and component reset.

void __thiscall PlayerCombatComponent::handleWeaponEvent(int *this, int *message)
{
  int msgId = *message;
  int localVar1;
  int localVar4;
  int *localPtr;

  if (msgId == DAT_012069c4) {                     // e.g., kWeaponEvent_Start
    setWeaponIdle();                                 // FUN_008d9d00
    destroyMessagePacket(message);                   // FUN_0046efc0
    return;
  }
  if (msgId == DAT_0120e93c) {                       // e.g., kWeaponEvent_Stop
    (*(void (__thiscall **)(int))(*(int *)(this - 0x3c) + 0x154))(); // call base method
    registerEvent(&DAT_0120e93c);                    // FUN_004086d0
    destroyMessagePacket(message);                   // FUN_0046efc0
    return;
  }
  if (msgId == DAT_0112adf0) {                       // e.g., kWeaponEvent_Switch
    // Extract target object from message payload
    if (*(int *)(message[1] + 4) == 0) {
      localVar4 = 0;
    } else {
      localVar4 = *(int *)(message[1] + 4) - 0x48;   // adjust for embedded object
    }
    // Get current weapon object from this
    if (*(int *)(this + 0x1f0) == 0) {
      localVar1 = 0;
    } else {
      localVar1 = *(int *)(this + 0x1f0) - 0x48;
    }
    if (localVar1 == localVar4) {
      // Same weapon – handle state
      if (*(char *)(this + 0x154) == '\0') {
        // Not in special mode
        beginWeaponSwitch(0);                        // FUN_008d9890
        if ((*(int *)(this + 0x174) != 0) && (*(int *)(this + 0x174) != 0x48)) {
          localPtr = (int *)(*(int *)(this + 0x174) - 0x48);
          (*(void (__thiscall **)(int,char *,int,int,int))(*localPtr + 0x84))
             (localVar4, "r_weapon", 0, 0, 0);       // play reload animation
        }
        int temp1 = 0;
        int temp2 = createSomeResource(0,0);         // FUN_006fbc40
        playSpatialEvent(0x85ce698e, 0, temp2, temp1); // FUN_007f96a0 – send hash event
        finishResourceCreation();                     // FUN_006fbc70
        destroyMessagePacket(message);               // FUN_0046efc0
        return;
      } else {
        // Special mode active
        doSpecialAction();                            // FUN_008d9990
        if ((*(int *)(this + 0x174) != 0) && (*(int *)(this + 0x174) != 0x48)) {
          if (*(int *)(this + 0x174) != 0) {
            localPtr = (int *)(*(int *)(this + 0x174) - 0x48);
            (*(void (__thiscall **)(int))(*localPtr + 0x7c))(); // call weapon method (e.g., stopFire)
            doWeaponPostAction();                     // FUN_008d9640
            destroyMessagePacket(message);            // FUN_0046efc0
            return;
          }
          (*(void (__thiscall **)(int))(*(int *)(0) + 0x7c))(); // safety – never hit
        }
        doWeaponPostAction();                         // FUN_008d9640
        destroyMessagePacket(message);                // FUN_0046efc0
        return;
      }
    }
  } else {
    if (msgId == *(int *)(this + 0x194)) {            // dynamic message ID (e.g., kWeaponEvent_Fire)
      *(char *)(this + 0x144) = 1;                   // set firing flag
      if ((*(int *)(this + 0x174) != 0) && (*(int *)(this + 0x174) != 0x48)) {
        if (*(int *)(this + 0x174) == 0) {
          (*(void (__thiscall **)(int))(*(int *)(0) + 0x70))(); // safety
        } else {
          localPtr = (int *)(*(int *)(this + 0x174) - 0x48);
          (*(void (__thiscall **)(int))(*localPtr + 0x70))();   // call startFire
        }
      }
    } else {
      if (msgId == *(int *)(this + 0x19c)) {          // dynamic message ID (e.g., kWeaponEvent_StopFire)
        *(char *)(this + 0x144) = 0;                  // clear firing flag
        if ((*(int *)(this + 0x174) != 0) && (*(int *)(this + 0x174) != 0x48)) {
          if (*(int *)(this + 0x174) == 0) {
            localPtr = (int *)0x0;
          } else {
            localPtr = (int *)(*(int *)(this + 0x174) - 0x48);
          }
          (*(void (__thiscall **)(int))(*localPtr + 0x6c))();   // call stopFire
        }
        doWeaponReset();                              // FUN_008d9170
        cleanupWeapon();                              // FUN_008d9190
        destroyMessagePacket(message);                // FUN_0046efc0
        return;
      }
      if ((msgId != DAT_0112a628) && (msgId != DAT_0112a5c4)) {
        goto exit;
      }
    }
    handleMisc();                                     // FUN_008d9c80
  }
exit:
  destroyMessagePacket(message);                      // FUN_0046efc0
  return;
}