// FUNC_NAME: SomeClass::copyStateOrSomething
void __fastcall SomeClass::copyStateOrSomething(undefined4 *param_1)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *in_EAX;
  undefined4 *puVar5;
  undefined4 *unaff_ESI;
  
  if (*(char *)*unaff_ESI == '\x02') {
    if (*(char *)*param_1 != '\x02') {
      *(undefined1 *)*in_EAX = 2;
      puVar5 = (undefined4 *)unaff_ESI[1];
      goto LAB_00585430;
    }
  }
  else if (*(char *)*param_1 != '\x02') {
    *(undefined1 *)*in_EAX = 0;
    return;
  }
  puVar5 = (undefined4 *)param_1[1];
  *(undefined1 *)*in_EAX = 2;
LAB_00585430:
  puVar1 = (undefined4 *)in_EAX[1];
  uVar2 = puVar5[1];
  uVar3 = puVar5[2];
  uVar4 = puVar5[3];
  *puVar1 = *puVar5;
  puVar1[1] = uVar2;
  puVar1[2] = uVar3;
  puVar1[3] = uVar4;
  uVar2 = puVar5[5];
  uVar3 = puVar5[6];
  uVar4 = puVar5[7];
  puVar1[4] = puVar5[4];
  puVar1[5] = uVar2;
  puVar1[6] = uVar3;
  puVar1[7] = uVar4;
  return;
}