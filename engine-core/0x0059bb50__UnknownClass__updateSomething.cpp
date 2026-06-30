// FUNC_NAME: UnknownClass::updateSomething
void __thiscall updateSomething(uint *this, int param_2)
{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  byte local_21;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  if ((*this & 1) == 0) {
    local_21 = FUN_00595950(&local_20);
    (**(code **)(*DAT_012055a8 + 4))(local_20,local_1c,local_18,0x3f800000,param_2);
  }
  else {
    bVar2 = FUN_00595610();
    bVar3 = FUN_00595610();
    local_21 = FUN_00595610();
    local_21 = bVar2 & bVar3 & local_21;
    *(undefined4 *)(param_2 + 0xc) = DAT_00e2b1a4;
  }
  pbVar1 = (byte *)this[1];
  if ((pbVar1 != (byte *)0x0) && ((*pbVar1 & 4) != 0)) {
    (**(code **)(*DAT_012055a8 + 0x18))(param_2,pbVar1 + 0x10,&local_20);
    (**(code **)(*DAT_012055a8 + 0x10))(&local_20,param_2);
  }
  if (local_21 != 0) {
    *this = *this | 2;
  }
  return;
}