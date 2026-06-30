// FUNC_NAME: EARSObject::constructor
void EARSObject::constructor(int param_1, undefined4 param_2)
{
  int *piVar1;
  undefined8 *puVar2;
  
  if (param_1 != 0) {
    FUN_004dec70(param_1,param_2);
    piVar1 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_FUN_01125158;
    *piVar1 = *piVar1 + 4;
    puVar2 = (undefined8 *)(*piVar1 + 3U & 0xfffffffc);
    *piVar1 = (int)puVar2;
    *puVar2 = CONCAT44(param_2,param_1);
    *piVar1 = *piVar1 + 8;
  }
  return;
}