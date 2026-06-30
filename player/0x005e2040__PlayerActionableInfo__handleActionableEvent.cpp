// FUNC_NAME: PlayerActionableInfo::handleActionableEvent
uint __thiscall PlayerActionableInfo::handleActionableEvent(int thisPtr, int eventData)
{
  float fVar1;
  int in_EAX;
  uint uVar2;
  undefined2 extraout_var;
  undefined3 uVar3;
  int *piVar4;
  
  uVar2 = FUN_005dbc10(); // likely getCurrentTime() or some timing function
  if ((*(char *)(thisPtr + 0x1744) != '\0') && (in_EAX != 0)) {
    uVar2 = 0;
    piVar4 = (int *)(thisPtr + 0x490); // +0x490: array of 5 actionable entity IDs
    do {
      if (in_EAX == *piVar4) {
        thisPtr = uVar2 * 0x4a4 + 4 + thisPtr; // +0x4: base offset, 0x4a4 per slot
        FUN_005e9440(); // likely processActionableEventStart
        fVar1 = *(float *)(eventData + 4); // eventData+4: some float parameter
        uVar3 = CONCAT21(extraout_var,
                         (fVar1 == DAT_00e2b05c) << 6 | (NAN(fVar1) || NAN(DAT_00e2b05c)) << 2 | 2U
                         | fVar1 < DAT_00e2b05c);
        if (fVar1 == DAT_00e2b05c) {
          FUN_005e86e0(); // likely completeActionableEvent
          FUN_005e86e0(); // second call for cleanup
          uVar3 = 0;
          *(undefined4 *)(thisPtr + 0x1fc) = 0; // +0x1fc: event state flag
          *(undefined4 *)(thisPtr + 0x200) = 0; // +0x200: event timer
        }
        return CONCAT31(uVar3,1);
      }
      uVar2 = uVar2 + 1;
      piVar4 = piVar4 + 0x129; // 0x129 * 4 = 0x4a4 bytes per slot
    } while ((int)uVar2 < 5);
  }
  return uVar2 & 0xffffff00;
}