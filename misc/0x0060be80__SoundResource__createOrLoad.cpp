// FUNC_NAME: SoundResource::createOrLoad
undefined4 * __thiscall SoundResource::createOrLoad(int param_1,undefined4 param_2,uint param_3)

{
  undefined4 *puVar1;
  undefined4 *in_EAX;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  void *unaff_ESI;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (in_EAX == (undefined4 *)0x0) {
    local_4 = 0;
    local_c = 2;
    local_8 = 0x10;
    in_EAX = (undefined4 *)(**(code **)*DAT_01205868)(0x20,&local_c);
    in_EAX[1] = in_EAX;
  }
  else {
    in_EAX[1] = 0;
  }
  uVar4 = 0;
  in_EAX[3] = param_1;
  puVar1 = in_EAX + 5;
  *puVar1 = 0;
  *(undefined1 *)(in_EAX + 2) = 0;
  *(undefined2 *)(in_EAX + 4) = 0;
  *(undefined2 *)((int)in_EAX + 0x12) = 0;
  uVar2 = 1;
  if ((param_3 & 2) == 0) {
    uVar2 = 2;
  }
  if ((param_3 & 4) != 0) {
    uVar4 = 0x20;
  }
  if ((param_3 & 8) != 0) {
    uVar4 = uVar4 | 0x200;
    uVar2 = ~param_3 & 2;
    *(undefined1 *)(in_EAX + 2) = 1;
  }
  if ((param_3 & 0x10) != 0) {
    uVar4 = uVar4 | 8;
  }
  iVar3 = (**(code **)(*DAT_01205750 + 0x6c))(DAT_01205750,param_1 * 2,uVar4,0x65,uVar2,in_EAX,0);
  if (iVar3 == 0) {
    if (unaff_ESI != (void *)0x0) {
      uVar5 = 0;
      if (*(char *)(in_EAX + 2) != '\0') {
        uVar5 = 0x3000;
      }
      (**(code **)(*(int *)*in_EAX + 0x2c))((int *)*in_EAX,0,0,puVar1,uVar5);
      _memcpy((void *)*puVar1,unaff_ESI,param_1 * 2);
      FUN_0060be40();
      (**(code **)(*(int *)*in_EAX + 0x30))((int *)*in_EAX);
    }
  }
  else if (iVar3 == -0x7789fe84) {
    (*(code *)PTR_FUN_00f15a3c)(2);
    return in_EAX;
  }
  return in_EAX;
}