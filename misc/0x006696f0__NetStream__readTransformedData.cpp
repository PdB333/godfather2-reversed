// FUNC_NAME: NetStream::readTransformedData
int readTransformedData(undefined4 unusedParam, int *inputBuffer, undefined4 *outputLength)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int extraout_ECX;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  void *local_24;
  undefined1 local_20 [16];
  undefined1 local_10 [16];
  
  iVar1 = inputBuffer[2];
  *outputLength = 0;
  if ((iVar1 == 1) || ((*inputBuffer < 2 && (*(uint *)inputBuffer[3] < 2)))) {
    return -3;
  }
  local_24 = _calloc(4,0x40);
  if (local_24 == (void *)0x0) {
    return -2;
  }
  local_30 = 0;
  local_2c = 0x40;
  local_28 = 0;
  iVar1 = startDecryption(); // +0x14?
  if (iVar1 != 0) {
    return iVar1;
  }
  iVar1 = processChunk(&local_30,1,&local_30);
  if (iVar1 != 0) goto LAB_0066987b;
  iVar1 = advanceStreamPosition();
  if (iVar1 != 0) goto LAB_0066987b;
  iVar2 = getStreamLength();
  iVar1 = decryptBlock(local_10,iVar2,local_10,0);
  if (iVar1 == 0) {
    iVar1 = verifyChecksum();
    if (iVar1 == 0) {
      iVar1 = readTransform(inputBuffer,local_10,unusedParam,local_20);
      if (iVar1 == 0) {
        iVar3 = checkStreamReady();
        if ((iVar3 != 0) && (iVar3 = getNextBlock(), iVar3 != 0)) {
          iVar3 = 1;
          if (0 < iVar2 + -1) {
            do {
              iVar4 = getNextBlock();
              if (iVar4 == 0) break;
              iVar1 = applyTransform(local_20,unusedParam,local_20);
              if ((iVar1 != 0) || (iVar4 = checkStreamReady(), iVar4 == 0)) goto LAB_00669869;
              iVar3 = iVar3 + extraout_ECX;
            } while (iVar3 <= iVar2 + -1);
          }
          iVar2 = getNextBlock();
          if (iVar2 != 0) goto LAB_00669869;
        }
        *outputLength = 1;
      }
LAB_00669869:
      cleanupTransformState();
    }
  }
  cleanupTransformState();
LAB_0066987b:
  cleanupTransformState();
  return iVar1;
}