// FUNC_NAME: PlayerSM::processHandFirearmSwitch
void __fastcall PlayerSM::processHandFirearmSwitch(int *thisObj)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 uStack_24;
  undefined1 local_20 [4];
  undefined4 uStack_1c;
  
  if ((((uint)thisObj[0xaf] >> 0xb & 1) == 0) && (((uint)thisObj[0xaf] >> 0xc & 1) == 0)) {
    // +0x104 = vtable offset for GetSkeleton (or similar)
    (**(code **)(*thisObj + 0x104))(local_20);
    iVar3 = FUN_00471610();
    piVar1 = thisObj + 0x107;
    cVar2 = FUN_006a89c0(piVar1,CONCAT44(*(undefined4 *)(iVar3 + 0x34),uStack_24),uStack_1c,
                         thisObj[0xcd]);
    if (cVar2 != '\0') {
      thisObj[0xaf] = thisObj[0xaf] | 0x1000;
      FUN_006a8980(piVar1);
      FUN_006a8790(piVar1);
    }
  }
  return;
}