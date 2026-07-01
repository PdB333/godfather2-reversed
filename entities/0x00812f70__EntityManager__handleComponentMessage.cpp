// FUNC_NAME: EntityManager::handleComponentMessage
void __thiscall EntityManager::handleComponentMessage(int this, int *param_2)
{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int local_8;
  
  if (*param_2 == DAT_012067ac) {
    if (*(int *)(param_2[1] + 0xc) == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = *(undefined4 *)(*(int *)(param_2[1] + 0xc) + 0x1c);
    }
    iVar2 = FUN_004025a0(uVar1); // getComponentByType?
    if (iVar2 == 0) {
      local_8 = -0x1e98fd1; // sentinel value
    }
    else {
      local_8 = *(int *)(iVar2 + 0x2c); // component data offset +0x2c
    }
    uVar5 = 0;
    if (*(int *)(this + 0x14) != 0) { // component count
      iVar2 = 0;
      do {
        piVar4 = (int *)(*(int *)(this + 0x10) + iVar2); // component array +0x10
        if (piVar4[3] == local_8) { // compare component type ID at offset +0xc
          if (piVar4[2] != 0) { // check if component is active
            iVar3 = FUN_004025a0(piVar4[2]); // get component instance
            if (iVar3 != 0) {
              FUN_004048c0(iVar3,0); // detach/remove component
            }
            piVar4[2] = 0;
          }
          if (*piVar4 == 0) { // check if component was removed
            FUN_00812df0(uVar5); // compact component array
            uVar5 = uVar5 - 1;
            iVar2 = iVar2 + -0x10;
          }
        }
        uVar5 = uVar5 + 1;
        iVar2 = iVar2 + 0x10; // each component entry is 0x10 bytes
      } while (uVar5 < *(uint *)(this + 0x14));
      return;
    }
  }
  else if (*param_2 == DAT_01206794) {
    if (*(int *)(param_2[1] + 0xc) == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = *(undefined4 *)(*(int *)(param_2[1] + 0xc) + 0x1c);
    }
    iVar2 = FUN_004025a0(uVar1); // getComponentByType?
    if (iVar2 == 0) {
      param_2 = (int *)0xfe16702f; // error sentinel
    }
    else {
      param_2 = *(int **)(iVar2 + 0x2c); // component ID
    }
    uVar5 = 0;
    if (*(uint *)(this + 0x14) != 0) { // component count
      piVar4 = (int *)(*(int *)(this + 0x10) + 0xc); // start at first component type ID
      while ((int *)*piVar4 != param_2) { // search for matching type
        uVar5 = uVar5 + 1;
        piVar4 = piVar4 + 4; // each entry is 4 bytes (type ID)
        if (*(uint *)(this + 0x14) <= uVar5) {
          return;
        }
      }
      FUN_004035c0(uVar1,8,this); // enable/activate component with flag 8
    }
  }
  return;
}