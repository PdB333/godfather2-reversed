// FUNC_NAME: StreamBuffer::readByte
void StreamBuffer::readByte(void)
{
  int iVar1;
  int *piVar2;
  uint *in_EAX;
  byte *pbVar3;
  undefined4 uVar4;
  uint uVar5;
  int local_4;
  
  // this->bufferSize (offset +0x24 = in_EAX[9])
  iVar1 = *(int *)in_EAX[9];
  *(int *)in_EAX[9] = iVar1 + -1;
  if (iVar1 == 0) {
    piVar2 = (int *)in_EAX[9];
    pbVar3 = (byte *)(*(code *)piVar2[2])(0,piVar2[3],&local_4);
    if ((pbVar3 == (byte *)0x0) || (local_4 == 0)) {
      uVar5 = 0xffffffff;
    }
    else {
      piVar2[1] = (int)pbVar3;
      *piVar2 = local_4 + -1;
      uVar5 = (uint)*pbVar3;
      piVar2[1] = (int)(pbVar3 + 1);
    }
  }
  else {
    pbVar3 = *(byte **)(in_EAX[9] + 4);
    uVar5 = (uint)*pbVar3;
    *(byte **)(in_EAX[9] + 4) = pbVar3 + 1;
  }
  // this->bytesRead (offset +0x04 = in_EAX[1])
  in_EAX[1] = in_EAX[1] + 1;
  // this->currentByte (offset +0x00 = *in_EAX)
  *in_EAX = uVar5;
  if (0x7ffffffd < (int)in_EAX[1]) {
    uVar4 = FUN_00636c00("too many %s (limit=%d)","lines in a chunk",0x7ffffffd);
    FUN_00638b80(uVar4);
  }
  return;
}