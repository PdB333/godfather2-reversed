// FUNC_NAME: NetConnection::processGhostUpdatePacket
void __thiscall NetConnection::processGhostUpdatePacket(int this, uint updateFlags, uint *ghostData, uint packetSeq, uint arg5, uint arg6, uint arg7, uint arg8, ulonglong *extraData, int isServer, uint *reverseGhostData)
{
  uint *ghostDataPtr;
  ulonglong *extraDataPtr;
  char flag;
  ulonglong *eaxData;
  int clientId;
  int i;
  uint ghostFlags;
  uint localVal;

  extraDataPtr = extraData;
  extraData = (ulonglong *)0x0;
  if (this == 0) {
    if (ghostData != (uint *)0x0) {
      goto LAB_005b2cc4;
    }
    FUN_0059bf00(); // likely assert failed or error
  }
  else if (ghostData != (uint *)0x0) {
    goto LAB_005b2cc4;
  }
  // Allocate ghost data if not provided
  FUN_005b24b0(updateFlags, packetSeq, this, arg5, arg6, arg7, arg8, &ghostData, &extraData);
  if (ghostData == (uint *)0x0) {
    return;
  }
LAB_005b2cc4:
  clientId = isServer;
  ghostDataPtr = ghostData;
  if (ghostData[0x14] == 0) { // +0x50: check if already initialized?
    if (extraDataPtr != (ulonglong *)0x0) {
      // Copy 64 bytes from extraData to ghostData+0x10
      *(ulonglong *)(ghostData + 4) = *extraDataPtr;
      *(ulonglong *)(ghostData + 6) = extraDataPtr[1];
      *(ulonglong *)(ghostData + 8) = extraDataPtr[2];
      *(ulonglong *)(ghostData + 10) = extraDataPtr[3];
    }
    // eaxData likely comes from a preceding operation (register return)
    eaxData = someReturnedPointer; // placeholder for in_EAX
    if (eaxData != (ulonglong *)0x0) {
      // Copy 24 bytes from eaxData to ghostData+0x38
      *(ulonglong *)(ghostData + 0xe) = *eaxData;
      *(ulonglong *)(ghostData + 0x10) = eaxData[1];
      *(ulonglong *)(ghostData + 0x12) = eaxData[2];
    }
  }
  if (isServer != 0) {
    flag = FUN_005a1a60(); // check permission or game state
    if (flag == '\0') {
      FUN_0059bf00(); // error
    }
    i = FUN_005a19c0(); // get current client/session ID
    *(int *)(i + 0x18) = clientId; // store something at offset 0x18
  }
  if ((extraData != (ulonglong *)0x0) && (i = FUN_005a3f20(), **(int **)(i + 8) == 5)) {
    // Check global array at DAT_0119a9cc + 0x1d14 for existing pointer
    i = 0;
    int *arrayPtr = (int *)(DAT_0119a9cc + 0x1d14);
    do {
      if ((uint *)*arrayPtr == ghostDataPtr) {
        goto LAB_005b2da7;
      }
      i = i + 1;
      arrayPtr = arrayPtr + 1;
    } while (i < 0x200); // 512 entries
    // If not found, likely destroy/cleanup ghost data
    FUN_005b9140(ghostDataPtr);
  }
LAB_005b2da7:
  ghostFlags = *ghostDataPtr & 0x7fff;
  if ((((*ghostDataPtr & 0x8000) != 0) && // high bit set
      ((ghostFlags == 0xd || ghostFlags == 0x12)) && // ghostType is 13 or 18
      (reverseGhostData != (uint *)0x0)) &&
     ((*reverseGhostData & 0x8000) != 0)) {
    localVal = FUN_005bc1e0(); // start iteration?
    int *iterator = (int *)FUN_005bb260(); // get first?
    while (iterator != (int *)0x0) {
      // Apply some effect/update for each ghost
      FUN_005ad5b0(ghostDataPtr, 0, *(undefined4 *)(*iterator + 0xc), iterator[1], 1, 1);
      iterator = (int *)FUN_005bb2a0(localVal); // next
    }
  }
  return;
}