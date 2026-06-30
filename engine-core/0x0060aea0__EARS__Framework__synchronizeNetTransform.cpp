// FUNC_NAME: EARS::Framework::synchronizeNetTransform
void __thiscall synchronizeNetTransform(undefined4 thisPtr, uint transformIndex, int srcData, int floatCount)
{
  float fVar1;
  bool bChanged;
  float *pfDest;
  float *pfSrc;
  int i;
  int remaining;
  uint uIndex;
  undefined *puDestBase;
  
  if (transformIndex != 0) {
    // Byte count = floatCount * 4
    int byteCount = floatCount * 4;
    uIndex = transformIndex & 0xff;
    bChanged = false;
    
    // Select buffer based on high bit (0x80000000) - client vs server transforms?
    if ((transformIndex & 0x80000000) == 0) {
      // +0x4 per slot, accessed at +0x10 per index from DAT_011d97f0 (likely a global transform buffer)
      puDestBase = (undefined *)(&DAT_011d97f0 + uIndex * 0x10);
    } else {
      puDestBase = (undefined *)(&DAT_011ea8f0 + uIndex * 0x10);
    }
    
    i = 0;
    if (3 < byteCount) {
      // Process 4 floats at a time (16 bytes)
      pfSrc = (float *)(srcData + 0xc);
      int loopCount = ((byteCount - 4U) >> 2) + 1;
      pfDest = (float *)(puDestBase + 4);
      i = loopCount * 4;
      do {
        if (pfDest[-1] != pfSrc[-3]) {
          bChanged = true;
          pfDest[-1] = pfSrc[-3];
        }
        fVar1 = *(float *)((srcData - (int)puDestBase) + (int)pfDest);
        if (*pfDest != fVar1) {
          bChanged = true;
          *pfDest = fVar1;
        }
        if (pfDest[1] != pfSrc[-1]) {
          bChanged = true;
          pfDest[1] = pfSrc[-1];
        }
        if (pfDest[2] != *pfSrc) {
          bChanged = true;
          pfDest[2] = *pfSrc;
        }
        pfDest = pfDest + 4;
        pfSrc = pfSrc + 4;
        loopCount = loopCount + -1;
      } while (loopCount != 0);
    }
    
    if (i < byteCount) {
      // Process remaining floats
      pfDest = (float *)(puDestBase + i * 4);
      remaining = byteCount - i;
      do {
        fVar1 = *(float *)((int)pfDest + (srcData - (int)puDestBase));
        if (*pfDest != fVar1) {
          bChanged = true;
          *pfDest = fVar1;
        }
        pfDest = pfDest + 1;
        remaining = remaining + -1;
      } while (remaining != 0);
    }
    
    if (bChanged) {
      if ((transformIndex & 0x80000000) != 0) {
        // If server-side buffer, call through vtable at offset 0x178
        // Likely marks dirty/needs update for remote clients
        (**(code **)(*DAT_01205750 + 0x178))();
        return;
      }
      // If client-side buffer, call through vtable at offset 0x1b4
      // with processed data length (word aligned)
      (**(code **)(*DAT_01205750 + 0x1b4))
                (DAT_01205750, uIndex, puDestBase, (int)(floatCount + 3 + (floatCount + 3 >> 0x1f & 3U)) >> 2);
    }
  }
  return;
}