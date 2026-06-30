// FUNC_NAME: GameSession::handleMessageType9c
undefined4 __thiscall GameSession::handleMessageType9c(int this, int *messageData, float paramValue)
{
  char activeCheck;
  float clampedValue;

  if ((messageData != (int *)0x0) && (*(int *)(this + 0x580) != 0)) {  // +0x580: netConnection pointer
    // Clamp paramValue to valid range [0.0, DAT_00e2b1a4]
    clampedValue = 0.0f;
    if ((paramValue <= 0.0f) || (clampedValue = DAT_00e2b1a4, DAT_00e2b1a4 <= paramValue)) {
      paramValue = clampedValue;
    }

    // Message type 0x9c indicates a specific game state update
    if (*messageData == 0x9c) {
      activeCheck = isGameActive();  // FUN_005e3aa0: check if game is active
      if (activeCheck == '\0') {      // if game not active, skip duplicate check
        if (paramValue == *(float *)(this + 0x908c)) {  // +0x908c: current sync value
          return 0;  // no change
        }
      }
      // Store the new state from message data
      *(int *)(this + 0x9094) = messageData[1];  // +0x9094: state field A
      *(int *)(this + 0x9098) = messageData[2];  // +0x9098: state field B
      *(int *)(this + 0x909c) = messageData[3];  // +0x909c: state field C
      *(int *)(this + 0x90a0) = messageData[4];  // +0x90a0: state field D
      *(float *)(this + 0x908c) = paramValue;    // +0x908c: sync timestamp
      applyStateUpdate(this);  // FUN_005eef50: apply the new state
      *(char *)(this + 37000) = 1;  // +0x9088: flag indicating pending update
      return 1;
    }
  }
  return 0;
}