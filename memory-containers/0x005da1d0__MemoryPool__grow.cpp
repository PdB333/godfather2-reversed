// FUNC_NAME: MemoryPool::grow
void MemoryPool::grow(uint requestedCount, undefined4 param_2, int param_3)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 *unaff_ESI;
  
  uVar1 = requestedCount;
  iVar4 = unaff_ESI[2]; // +0x08: base pointer
  if (iVar4 == 0) {
    uVar7 = 0;
  }
  else {
    uVar7 = (unaff_ESI[4] - iVar4) / 0x28; // +0x10: end pointer, calculate current capacity
  }
  if (requestedCount != 0) {
    if (iVar4 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = (unaff_ESI[3] - iVar4) / 0x28; // +0x0C: allocation pointer, calculate used count
    }
    if (0x6666666U - iVar3 < requestedCount) { // Max capacity check (0x6666666 = 107374182)
      FUN_005d9ed0(); // handleOutOfMemory
      return;
    }
    if (iVar4 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = (unaff_ESI[3] - iVar4) / 0x28;
    }
    if (uVar7 < iVar3 + requestedCount) {
      // Need to reallocate
      if (0x6666666 - (uVar7 >> 1) < uVar7) {
        uVar7 = 0;
      }
      else {
        uVar7 = uVar7 + (uVar7 >> 1); // Grow by 50%
      }
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = (unaff_ESI[3] - iVar4) / 0x28;
      }
      if (uVar7 < iVar4 + requestedCount) {
        iVar4 = FUN_005d9a60(); // calculateNewSize
        uVar7 = iVar4 + requestedCount;
      }
      iVar3 = FUN_005da050(); // allocateNewBlock
      uVar2 = requestedCount >> 8;
      requestedCount = uVar2 << 8;
      uVar5 = FUN_005dab00(unaff_ESI[2],requestedCount,requestedCount); // copyElements
      requestedCount = uVar2 << 8;
      FUN_005da830(uVar5,requestedCount,requestedCount); // initializeNewElements
      requestedCount = uVar2 << 8;
      FUN_005dab00(param_3,requestedCount,requestedCount); // copyElements
      iVar4 = unaff_ESI[2];
      if (iVar4 == 0) {
        iVar6 = 0;
      }
      else {
        iVar6 = (unaff_ESI[3] - iVar4) / 0x28;
      }
      if (iVar4 != 0) {
        (**(code **)(*(int *)*unaff_ESI + 4))(iVar4,((unaff_ESI[4] - iVar4) / 0x28) * 0x28); // free old block
      }
      unaff_ESI[4] = iVar3 + uVar7 * 0x28; // +0x10: new end
      unaff_ESI[3] = iVar3 + (uVar1 + iVar6) * 0x28; // +0x0C: new allocation pointer
      unaff_ESI[2] = iVar3; // +0x08: new base
      return;
    }
    uVar1 = unaff_ESI[3];
    if ((uint)((int)(uVar1 - param_3) / 0x28) < requestedCount) {
      // Need to shift elements
      iVar4 = requestedCount * 0x28;
      FUN_005da6d0(uVar1,iVar4 + param_3); // shiftElements
      requestedCount = uVar1 & 0xffffff00;
      FUN_005da830(unaff_ESI[3],requestedCount,requestedCount); // initializeNewElements
      unaff_ESI[3] = unaff_ESI[3] + iVar4; // +0x0C: update allocation pointer
      FUN_005da8a0(param_3); // cleanup
      return;
    }
    uVar5 = FUN_005da6d0(uVar1,uVar1); // shiftElements
    unaff_ESI[3] = uVar5; // +0x0C: update allocation pointer
    FUN_005da710(param_3,uVar1 + requestedCount * -0x28); // moveElements
    FUN_005da8a0(param_3); // cleanup
  }
  return;
}