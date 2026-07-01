// FUNC_NAME: EARSObject::createInstance
undefined4 EARSObject::createInstance(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 unaff_retaddr;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80();
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  iVar2 = (**(code **)*puVar1)(0xe0,&local_c);
  if (iVar2 != 0) {
    uVar3 = FUN_008cd5a0(unaff_retaddr,local_4);
    return uVar3;
  }
  return 0;
}