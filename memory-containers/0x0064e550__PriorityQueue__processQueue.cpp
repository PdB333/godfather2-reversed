// FUNC_NAME: PriorityQueue::processQueue
void __thiscall PriorityQueue::processQueue(int this, int param_2)
{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  
  if (*(int *)(this + 0x1c8) != 0) {
    FUN_0065b9d0();
  }
  piVar3 = (int *)(this + 0x1e0); // +0x1E0: queue head pointer
  piVar4 = *(int **)(param_2 + 0x14); // +0x14: input list
  piVar8 = piVar3;
  do {
    while( true ) {
      piVar2 = piVar4;
      if (piVar2 == (int *)0x0) {
        iVar6 = *piVar3;
        while( true ) {
          if (iVar6 == 0) {
            return;
          }
          iVar6 = *(int *)(this + 0x1ec) + 1; // +0x1EC: sequence counter
          puVar7 = (undefined4 *)*piVar3;
          if (puVar7[1] != iVar6) break;
          *(int *)(this + 0x1ec) = iVar6;
          iVar6 = puVar7[2];
          (**(code **)(*(int *)*puVar7 + 0x20))(this,1);
          if ((_DAT_01223cbc & 1) == 0) {
            _DAT_01223cbc = _DAT_01223cbc | 1;
            FUN_0064f120();
            _atexit((_func_4879 *)&LAB_00d513f0);
          }
          piVar8 = (int *)*piVar3;
          piVar4 = (int *)*piVar8;
          if (piVar4 != (int *)0x0) {
            piVar2 = piVar4 + 2;
            *piVar2 = *piVar2 + -1;
            if (*piVar2 == 0) {
              (**(code **)(*piVar4 + 8))();
            }
          }
          _DAT_01223cb0 = _DAT_01223cb0 + -1;
          *piVar8 = (int)DAT_01223cb8;
          DAT_01223cb8 = piVar8;
          *piVar3 = iVar6;
        }
        return;
      }
      piVar4 = (int *)piVar2[2];
      if (((int *)*piVar2)[4] == 0) break;
      (**(code **)(*(int *)*piVar2 + 0x20))(this,1);
      if ((_DAT_01223cbc & 1) == 0) {
        _DAT_01223cbc = _DAT_01223cbc | 1;
        FUN_0064f120();
        _atexit((_func_4879 *)&LAB_00d513f0);
      }
      piVar5 = (int *)*piVar2;
      if (piVar5 != (int *)0x0) {
        piVar1 = piVar5 + 2;
        *piVar1 = *piVar1 + -1;
        if (*piVar1 == 0) {
          (**(code **)(*piVar5 + 8))();
        }
      }
      _DAT_01223cb0 = _DAT_01223cb0 + -1;
      *piVar2 = (int)DAT_01223cb8;
      DAT_01223cb8 = piVar2;
    }
    if (*piVar8 != 0) {
      do {
        iVar6 = *piVar8;
        if (piVar2[1] <= *(int *)(iVar6 + 4)) break;
        piVar8 = (int *)(iVar6 + 8);
      } while (*(int *)(iVar6 + 8) != 0);
    }
    piVar2[2] = *piVar8;
    *piVar8 = (int)piVar2;
    piVar8 = piVar2 + 2;
  } while( true );
}