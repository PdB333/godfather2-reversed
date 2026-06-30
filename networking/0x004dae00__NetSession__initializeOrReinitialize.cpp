// FUNC_NAME: NetSession::initializeOrReinitialize
undefined4 * NetSession::initializeOrReinitialize(undefined4 *this, int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 local_50;
  undefined4 local_4c;
  char local_40 [20];
  int local_2c;
  undefined4 local_28;
  int local_8;
  
  pcVar3 = "{BADBADBA-BEEF-BEEF-555A-C1EA11091091}";
  puVar4 = this;
  for (iVar2 = 9; puVar5 = puVar4 + 1, iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar5 = *(undefined4 *)pcVar3;
    pcVar3 = pcVar3 + 4;
    puVar4 = puVar5;
  }
  *(undefined2 *)puVar5 = *(undefined2 *)pcVar3;
  *(char *)((int)puVar4 + 6) = pcVar3[2];
  *(undefined1 *)(this + 0xb) = 1;
  this[0x13] = 0;
  if (param_2 == 0) {
    *this = 2;
    this[0x14] = &DAT_00e36e5c;
  }
  else {
    cVar1 = FUN_004da120();
    if (cVar1 != '\0') {
      *this = 1;
      FUN_004da330(param_2);
      return this;
    }
    FUN_004d9500(param_2);
    FUN_004da910();
    if (local_40[0] == '\x01') {
      cVar1 = FUN_00445250();
      if (cVar1 == '\0') {
        *this = 2;
        this[0x14] = param_2;
      }
      else {
        *this = 0;
        FUN_004d9080(&local_28,local_50,local_4c);
        if (this + 1 != &local_28) {
          puVar4 = &local_28;
          puVar5 = this + 1;
          for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
          }
          *(undefined2 *)puVar5 = *(undefined2 *)puVar4;
          *(undefined1 *)((int)puVar5 + 2) = *(undefined1 *)((int)puVar4 + 2);
        }
      }
    }
    else {
      *this = 1;
      FUN_004d9d60(local_40);
      FUN_004d9ff0();
      if (local_8 != 0) {
        FUN_004da530();
        FUN_009c8eb0(local_8);
      }
    }
    if (local_2c != 0) {
      FUN_004d8be0();
      FUN_009c8eb0(local_2c);
      return this;
    }
  }
  return this;
}