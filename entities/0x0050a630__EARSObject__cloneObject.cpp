// FUNC_NAME: EARSObject::cloneObject
undefined4 * __thiscall EARSObject::cloneObject(undefined4 *this, undefined4 param_2, char param_3)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 in_EAX;
  undefined4 *src;
  void *dst;
  int *piVar4;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = 2;
  local_18 = 0x10;
  local_14 = 0;
  src = (undefined4 *)FUN_009c8ed0(0x60,&local_1c);
  if (src == (undefined4 *)0x0) {
    src = (undefined4 *)0x0;
  }
  else {
    src[0x13] = 0;
    src[0x14] = in_EAX;
    src[0x13] = param_2;
    piVar4 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011250a4;
    *piVar4 = *piVar4 + 4;
    *(undefined4 **)*piVar4 = src;
    *piVar4 = *piVar4 + 4;
    *(undefined4 *)*piVar4 = param_2;
    *piVar4 = *piVar4 + 4;
    *(undefined4 *)*piVar4 = in_EAX;
    *piVar4 = *piVar4 + 4;
  }
  uVar1 = this[1];
  uVar2 = this[2];
  uVar3 = this[3];
  *src = *this;
  src[1] = uVar1;
  src[2] = uVar2;
  src[3] = uVar3;
  uVar1 = this[5];
  uVar2 = this[6];
  uVar3 = this[7];
  src[4] = this[4];
  src[5] = uVar1;
  src[6] = uVar2;
  src[7] = uVar3;
  uVar1 = this[9];
  uVar2 = this[10];
  uVar3 = this[0xb];
  src[8] = this[8];
  src[9] = uVar1;
  src[10] = uVar2;
  src[0xb] = uVar3;
  uVar1 = this[0xd];
  uVar2 = this[0xe];
  uVar3 = this[0xf];
  src[0xc] = this[0xc];
  src[0xd] = uVar1;
  src[0xe] = uVar2;
  src[0xf] = uVar3;
  piVar4 = (int *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011250cc;
  *piVar4 = *piVar4 + 4;
  *(undefined4 **)*piVar4 = src;
  dst = (void *)(*piVar4 + 0x13U & 0xfffffff0);
  *piVar4 = (int)dst;
  _memcpy(dst,src,0x40);
  *piVar4 = *piVar4 + 0x40;
  src[0x12] = 0;
  src[0x11] = 0;
  src[0x10] = 0xffffffff;
  if (param_3 != '\\0') {
    piVar4 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011250e0;
    *piVar4 = *piVar4 + 4;
    *(undefined4 *)*piVar4 = param_2;
    *piVar4 = *piVar4 + 4;
    *(undefined4 **)*piVar4 = src;
    *piVar4 = *piVar4 + 4;
    *(undefined4 *)*piVar4 = 0xffffffff;
    *piVar4 = *piVar4 + 4;
  }
  return src;
}