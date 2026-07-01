// FUNC_NAME: CoverHintNodeManager::findCoverInRange
char __thiscall CoverHintNodeManager::findCoverInRange(void *this, void *sourceEntity, undefined4 *resultOut)
{
  int internalObj;
  int coverNodePtr;
  int i;
  char found;
  float distSq;
  CoverResult coverResult;
  int coverCountGlobal;
  int *coverListPtr;
  int coverCountLocal;
  
  // Get some object from the source entity (likely a physics object or bone position)
  internalObj = *(int *)((int)sourceEntity + 0x194);
  found = '\0';
  if (((internalObj != 0) && (internalObj != 0x48)) &&
      (internalObj = *(int *)(internalObj + 0xe8), internalObj != 0)) {
    // Distance threshold: source object's radius squared + constant
    distSq = *(float *)(internalObj + 0x2c) + DAT_00d5779c;
    distSq = distSq * distSq;
    
    // Clear output structure (64 bytes)
    _memset(&coverResult, 0, sizeof(coverResult));
    
    // Global cover list 1 (e.g., environmental low cover)
    coverListPtr = (int *)(DAT_0112e2e8 + 0x5c);
    coverCountGlobal = *(int *)(DAT_0112e2e8 + 0x60);
    for (i = 0; i < coverCountGlobal; i++) {
      coverNodePtr = *(int *)(*coverListPtr + i * 8);
      if (((coverNodePtr != 0) && (coverNodePtr != 0x48)) &&
          (found = checkOverlap(*(undefined4 *)(internalObj + 0x20),        // source X
                                *(undefined4 *)(internalObj + 0x28),        // source Z
                                DAT_00d8b374,                               // constant half-extent
                                distSq,                                     // squared distance
                                &coverResult), found != '\0')) {
        // Mark hit but continue (last hit remains)
      }
    }
    
    // Global cover list 2 (e.g., environmental high cover)
    coverListPtr = (int *)(DAT_0112e2e8 + 0x68);
    coverCountGlobal = *(int *)(DAT_0112e2e8 + 0x6c);
    for (i = 0; i < coverCountGlobal; i++) {
      coverNodePtr = *(int *)(*coverListPtr + i * 8);
      if (((coverNodePtr != 0) && (coverNodePtr != 0x48)) &&
          (found = checkOverlap(*(undefined4 *)(internalObj + 0x20),
                                *(undefined4 *)(internalObj + 0x28),
                                DAT_00d8b374,
                                distSq,
                                &coverResult), found != '\0')) {
      }
    }
    
    // Local cover list (dynamic cover hints attached to this manager)
    coverCountLocal = *(int *)((int)this + 0x130);
    for (i = 0; i < coverCountLocal; i++) {
      coverNodePtr = *(int *)(*(int *)((int)this + 0x12c) + i * 4);
      if ((coverNodePtr != 0) &&
          (found = checkOverlap(*(undefined4 *)(internalObj + 0x20),
                                *(undefined4 *)(internalObj + 0x28),
                                DAT_00d8b374,
                                distSq,
                                &coverResult), found != '\0')) {
      }
    }
    
    // If any cover found, copy result to output
    if (found != '\0') {
      *(undefined4 *)resultOut = coverResult.data0;
      *(undefined4 *)(resultOut + 1) = coverResult.data1;
      *(undefined4 *)(resultOut + 2) = coverResult.data2;
      *(undefined4 *)(resultOut + 3) = coverResult.data3;
      *(undefined4 *)(resultOut + 4) = coverResult.data4;
      *(undefined4 *)(resultOut + 5) = coverResult.data5;
      *(undefined4 *)(resultOut + 6) = coverResult.data6;
      *(undefined4 *)(resultOut + 7) = coverResult.data7;
      *(undefined4 *)(resultOut + 8) = coverResult.data8;
      *(undefined4 *)(resultOut + 9) = coverResult.data9;
      *(undefined4 *)(resultOut + 0xa) = coverResult.data10;
      *(undefined4 *)(resultOut + 0xb) = coverResult.data11;
      *(undefined4 *)(resultOut + 0xc) = coverResult.data12;
      *(undefined4 *)(resultOut + 0xd) = coverResult.data13;
      *(undefined4 *)(resultOut + 0xe) = coverResult.data14;
      *(undefined4 *)(resultOut + 0xf) = coverResult.data15;
    }
  }
  return found;
}