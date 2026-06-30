// FUNC_NAME: PacketStoreManager::storePacket
byte PacketStoreManager::storePacket(int *this, undefined4 *pPacketData, int packetType)
{
  int *pStorage;
  undefined4 *pSlot;
  undefined4 *pDest;
  int slotIndex;
  int loopCount;
  byte bResult;
  undefined4 *pLocalData;
  int localResult;
  int *pCallbackContext;
  
  pStorage = (int *)*this;
  // Store into first buffer (reliable unsequenced?)
  if (*(int *)(pStorage + 0x1880) < 8) {
    slotIndex = *(int *)(pStorage + 0x1880);
    pSlot = (undefined4 *)(slotIndex * 0xc0 + pStorage + 0x1280);
    loopCount = 0x30;
    do {
      *pSlot = *pPacketData;
      pPacketData = pPacketData + 1;
      pSlot = pSlot + 1;
      loopCount = loopCount + -1;
    } while (loopCount != 0);
    *(int *)(pStorage + 0x1880) = *(int *)(pStorage + 0x1880) + 1;
  }
  // Store into second buffer (sequenced?)
  pStorage = (int *)*this;
  if (*(int *)(pStorage + 0x3300) < 8) {
    slotIndex = *(int *)(pStorage + 0x3300);
    pDest = (undefined4 *)(slotIndex * 0xc0 + pStorage + 0x2d00);
    loopCount = 0x30;
    do {
      *pDest = *pPacketData;
      pPacketData = pPacketData + 1;
      pDest = pDest + 1;
      loopCount = loopCount + -1;
    } while (loopCount != 0);
    *(int *)(pStorage + 0x3300) = *(int *)(pStorage + 0x3300) + 1;
    bResult = 1;
  }
  else {
    bResult = 0;
  }
  // Execute callback if present
  if ((*(int *)(pStorage + 0x3a6c) != 0) || (*(int *)(pStorage + 0x3a58) != 0)) {
    pCallbackContext = (int *)(pStorage + 0x3350);
    pLocalData = pPacketData; // Note: pPacketData is now advanced from previous copies? Actually pPacketData is unchanged? The decompiler shows param_2 used again, but pPacketData was modified. This might be a bug in decompilation. Assume pPacketData still points to original data.
    localResult = packetType;
    if (*(code **)(pStorage + 0x3a6c) == (code *)0x0) {
      bResult = (**(code **)(pStorage + 0x3a58))(&pLocalData) & bResult;
    }
    else {
      bResult = (**(code **)(pStorage + 0x3a6c))((undefined4 *)(pStorage + 0x3a58),&pLocalData) & bResult;
    }
  }
  // Set first byte of packet data as result (may be intentional for return)
  *(byte *)pPacketData = bResult;
  // Based on packetType, choose additional storage
  if (packetType == 0) {
    pStorage = (int *)*this;
    if (*(int *)(pStorage + 0x25c0) < 8) {
      slotIndex = *(int *)(pStorage + 0x25c0);
      pDest = (undefined4 *)(slotIndex * 0xc0 + pStorage + 0x1fc0);
      loopCount = 0x30;
      do {
        *pDest = *pPacketData;
        pPacketData = pPacketData + 1;
        pDest = pDest + 1;
        loopCount = loopCount + -1;
      } while (loopCount != 0);
      *(int *)(pStorage + 0x25c0) = *(int *)(pStorage + 0x25c0) + 1;
    }
    else {
      *(byte *)pPacketData = 0;
    }
  }
  else if (packetType != 2) {
    goto LAB_00433585;
  }
  // For packetType == 2 (or fallthrough from else)
  pStorage = (int *)*this;
  if (*(int *)(pStorage + 0x1f20) < 8) {
    slotIndex = *(int *)(pStorage + 0x1f20);
    pDest = (undefined4 *)(slotIndex * 0xc0 + pStorage + 0x1920);
    loopCount = 0x30;
    do {
      *pDest = *pPacketData;
      pPacketData = pPacketData + 1;
      pDest = pDest + 1;
      loopCount = loopCount + -1;
    } while (loopCount != 0);
    *(int *)(pStorage + 0x1f20) = *(int *)(pStorage + 0x1f20) + 1;
    bResult = 1;
  }
  else {
    bResult = 0;
  }
  *(byte *)pPacketData = *(byte *)pPacketData & bResult;
  
LAB_00433585:
  if (packetType != 0) {
    return *(byte *)pPacketData;
  }
  // For packetType == 0, additional store
  pStorage = (int *)*this;
  if (7 < *(int *)(pStorage + 0x2c60)) {
    return 0;
  }
  slotIndex = *(int *)(pStorage + 0x2c60);
  pDest = (undefined4 *)(slotIndex * 0xc0 + pStorage + 0x2660);
  loopCount = 0x30;
  do {
    *pDest = *pPacketData;
    pPacketData = pPacketData + 1;
    pDest = pDest + 1;
    loopCount = loopCount + -1;
  } while (loopCount != 0);
  *(int *)(pStorage + 0x2c60) = *(int *)(pStorage + 0x2c60) + 1;
  return *(byte *)pPacketData;
}