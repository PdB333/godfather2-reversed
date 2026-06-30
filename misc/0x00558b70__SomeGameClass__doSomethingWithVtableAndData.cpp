// FUNC_NAME: SomeGameClass::doSomethingWithVtableAndData
int SomeGameClass::doSomethingWithVtableAndData(void)
{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *unaff_ESI;
  undefined4 uStack_30;
  undefined4 local_2c;
  int *apiStack_28 [2];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  // Call virtual function at vtable+0xa4, probably some kind of getter/state update
  (**(code **)(*(int *)*unaff_ESI + 0xa4))(&local_2c);
  uStack_20 = local_2c;
  uStack_1c = 0;
  if (unaff_ESI[7] == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = *(int *)(unaff_ESI[7] + 0x10);
  }
  // Set up some structure at offset +0x20,+0x24, etc.
  *(int **)(iVar5 + 0x20) = unaff_ESI + 9;
  *(undefined4 *)(iVar5 + 0x24) = uStack_30;
  *(undefined4 *)(iVar5 + 0x28) = local_2c;
  *(undefined4 *)(iVar5 + 0x2c) = 0;
  *(undefined1 *)(iVar5 + 0x48) = 1;  // Set some flag/boolean at +0x48
  iVar5 = unaff_ESI[7];
  if (*(int *)(iVar5 + 8) != 0) {
    apiStack_28[0] = unaff_ESI + 9;
    iVar5 = FUN_009f1820(apiStack_28,0);
    return iVar5;
  }
  iVar3 = *unaff_ESI;
  uVar1 = *(undefined4 *)(iVar3 + 0x104);
  uVar2 = *(undefined4 *)(iVar3 + 0x108);
  *(undefined4 *)(iVar5 + 0xd0) = *(undefined4 *)(iVar3 + 0x100);  // Copy data from vtable region
  *(undefined4 *)(iVar5 + 0xd4) = uVar1;
  *(undefined4 *)(iVar5 + 0xd8) = uVar2;
  uVar4 = DAT_00e2b1a4;  // Some global/game data
  *(undefined4 *)(iVar5 + 0xdc) = uVar4;
  return iVar3 + 0x100;  // Return pointer to stored data
}