// FUNC_NAME: FixedSizeStack::pop
void __fastcall FixedSizeStack::pop(undefined4 *outData, int *count, int dataArray)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int newCount;
  undefined4 *src;
  
  if (0 < *count) {
    newCount = *count + -1;
    *count = newCount;
    src = (undefined4 *)(newCount * 0x40 + dataArray);
    uVar1 = src[1];
    uVar2 = src[2];
    uVar3 = src[3];
    *outData = *src;
    outData[1] = uVar1;
    outData[2] = uVar2;
    outData[3] = uVar3;
    uVar1 = src[5];
    uVar2 = src[6];
    uVar3 = src[7];
    outData[4] = src[4];
    outData[5] = uVar1;
    outData[6] = uVar2;
    outData[7] = uVar3;
    uVar1 = src[9];
    uVar2 = src[10];
    uVar3 = src[0xb];
    outData[8] = src[8];
    outData[9] = uVar1;
    outData[10] = uVar2;
    outData[0xb] = uVar3;
    uVar1 = src[0xd];
    uVar2 = src[0xe];
    uVar3 = src[0xf];
    outData[0xc] = src[0xc];
    outData[0xd] = uVar1;
    outData[0xe] = uVar2;
    outData[0xf] = uVar3;
  }
  return;
}