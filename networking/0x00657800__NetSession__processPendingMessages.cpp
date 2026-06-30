// FUNC_NAME: NetSession::processPendingMessages
void NetSession::processPendingMessages(void *param_1, int param_2)

{
  code *pcVar1;
  char cVar2;
  int *piVar3;
  undefined1 local_38c [8];
  undefined1 local_384 [8];
  undefined1 local_37c [256];
  undefined1 local_27c [636];
  
  piVar3 = (int *)FUN_00655250();
  if (piVar3 != (int *)0x0) {
    FUN_0064b9e0(0x40,local_384);
    FUN_0064b9e0(0x40,local_38c);
    cVar2 = FUN_006549b0();
    if (cVar2 == '\\0') {
      cVar2 = FUN_006549b0();
      if (cVar2 == '\\0') {
        *(uint *)(param_2 + 0x18) = *(int *)(param_2 + 0x18) + 7U & 0xfffffff8;
        if (*(char *)((int)piVar3 + 0x131) != '\\0') {
          FUN_0065a5e0(local_27c);
          cVar2 = FUN_0064ca10(param_2,local_27c);
          if (cVar2 == '\\0') {
            FUN_00656aa0();
            return;
          }
          FUN_00656aa0();
        }
        FUN_0064c6b0(local_37c);
        pcVar1 = *(code **)(*piVar3 + 0x10);
        piVar3[0x6d] = 8;
        (*pcVar1)(3,local_37c);
        FUN_006552f0(param_1,piVar3);
      }
    }
  }
  return;
}