// FUNC_NAME: RBTree::insertNode
void __thiscall RBTree::insertNode(int this, int *outNode, char param_3, undefined4 *param_4, int *param_5)
{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  undefined1 local_40 [4];
  uint local_3c;
  undefined4 local_2c;
  uint local_28;
  undefined **local_24;
  char *local_20;
  uint local_18;
  undefined4 local_8;
  uint local_4;
  
  if (0x15555553 < *(uint *)(this + 8)) {
    local_28 = 0xf;
    local_2c = 0;
    local_3c = local_3c & 0xffffff00;
    FUN_0043f9f0("map/set<T> too long",0x13);
    local_20 = "unknown";
    local_24 = &PTR_FUN_00da9810;
    local_4 = 0xf;
    local_8 = 0;
    local_18 = local_18 & 0xffffff00;
    FUN_0043eeb0(local_40,0,0xffffffff);
    local_24 = &PTR_FUN_00da9828;
    if (DAT_0113d3a0 != (code *)0x0) {
      (*DAT_0113d3a0)(&local_24);
    }
    (*(code *)local_24[2])();
    std::_Throw((exception *)&local_24);
    local_24 = &PTR_FUN_00da9810;
    if (0xf < local_4) {
      FUN_009c8eb0(local_18);
    }
    local_4 = 0xf;
    local_8 = 0;
    local_18 = local_18 & 0xffffff00;
    local_24 = &PTR_LAB_00e31044;
    if (0xf < local_28) {
      FUN_009c8eb0(local_3c);
    }
  }
  iVar4 = *(int *)(this + 4);
  piVar3 = (int *)FUN_009c8e50(0x1c);
  if (piVar3 != (int *)0x0) {
    *piVar3 = iVar4;
    piVar3[1] = (int)param_4;
    piVar3[2] = iVar4;
    piVar3[3] = *param_5;
    FUN_008eb820(param_5 + 1);
    *(undefined1 *)(piVar3 + 6) = 0;
    *(undefined1 *)((int)piVar3 + 0x19) = 0;
  }
  *(int *)(this + 8) = *(int *)(this + 8) + 1;
  if (param_4 == *(undefined4 **)(this + 4)) {
    (*(undefined4 **)(this + 4))[1] = piVar3;
    **(undefined4 **)(this + 4) = piVar3;
    iVar4 = *(int *)(this + 4);
  }
  else {
    if (param_3 != '\0') {
      *param_4 = piVar3;
      if (param_4 == (undefined4 *)**(int **)(this + 4)) {
        **(int **)(this + 4) = (int)piVar3;
      }
      goto LAB_008ed535;
    }
    param_4[2] = piVar3;
    iVar4 = *(int *)(this + 4);
    if (param_4 != *(undefined4 **)(iVar4 + 8)) goto LAB_008ed535;
  }
  *(int **)(iVar4 + 8) = piVar3;
LAB_008ed535:
  cVar1 = *(char *)(piVar3[1] + 0x18);
  piVar7 = piVar3;
  do {
    if (cVar1 != '\0') {
      *(undefined1 *)(*(int *)(*(int *)(this + 4) + 4) + 0x18) = 1;
      *outNode = this;
      outNode[1] = (int)piVar3;
      return;
    }
    piVar5 = piVar7 + 1;
    piVar6 = (int *)*piVar5;
    piVar2 = (int *)piVar6[1];
    if (piVar6 == (int *)*piVar2) {
      iVar4 = piVar2[2];
      if (*(char *)(iVar4 + 0x18) == '\0') goto LAB_008ed604;
      if (piVar7 == (int *)piVar6[2]) {
        piVar7 = (int *)piVar6[2];
        piVar6[2] = *piVar7;
        if (*(char *)(*piVar7 + 0x19) == '\0') {
          *(int **)(*piVar7 + 4) = piVar6;
        }
        piVar5 = piVar6 + 1;
        piVar7[1] = piVar6[1];
        if (piVar6 == *(int **)(*(int *)(this + 4) + 4)) {
          *(int **)(*(int *)(this + 4) + 4) = piVar7;
        }
        else {
          piVar2 = (int *)*piVar5;
          if (piVar6 == (int *)*piVar2) {
            *piVar2 = (int)piVar7;
          }
          else {
            piVar2[2] = (int)piVar7;
          }
        }
        *piVar7 = (int)piVar6;
        *piVar5 = (int)piVar7;
        piVar7 = piVar6;
      }
      *(undefined1 *)(*piVar5 + 0x18) = 1;
      *(undefined1 *)(*(int *)(*piVar5 + 4) + 0x18) = 0;
      piVar5 = *(int **)(*piVar5 + 4);
      piVar6 = (int *)*piVar5;
      *piVar5 = piVar6[2];
      if (*(char *)(piVar6[2] + 0x19) == '\0') {
        *(int **)(piVar6[2] + 4) = piVar5;
      }
      piVar6[1] = piVar5[1];
      if (piVar5 == *(int **)(*(int *)(this + 4) + 4)) {
        *(int **)(*(int *)(this + 4) + 4) = piVar6;
        piVar6[2] = (int)piVar5;
      }
      else {
        piVar2 = (int *)piVar5[1];
        if (piVar5 == (int *)piVar2[2]) {
          piVar2[2] = (int)piVar6;
          piVar6[2] = (int)piVar5;
        }
        else {
          *piVar2 = (int)piVar6;
          piVar6[2] = (int)piVar5;
        }
      }
LAB_008ed677:
      piVar5[1] = (int)piVar6;
    }
    else {
      iVar4 = *piVar2;
      if (*(char *)(iVar4 + 0x18) != '\0') {
        if (piVar7 == (int *)*piVar6) {
          FUN_008e9fe0(piVar6);
          piVar7 = piVar6;
        }
        *(undefined1 *)(piVar7[1] + 0x18) = 1;
        *(undefined1 *)(*(int *)(piVar7[1] + 4) + 0x18) = 0;
        piVar5 = *(int **)(piVar7[1] + 4);
        piVar6 = (int *)piVar5[2];
        piVar5[2] = *piVar6;
        if (*(char *)(*piVar6 + 0x19) == '\0') {
          *(int **)(*piVar6 + 4) = piVar5;
        }
        piVar6[1] = piVar5[1];
        if (piVar5 == *(int **)(*(int *)(this + 4) + 4)) {
          *(int **)(*(int *)(this + 4) + 4) = piVar6;
        }
        else {
          piVar2 = (int *)piVar5[1];
          if (piVar5 == (int *)*piVar2) {
            *piVar2 = (int)piVar6;
          }
          else {
            piVar2[2] = (int)piVar6;
          }
        }
        *piVar6 = (int)piVar5;
        goto LAB_008ed677;
      }
LAB_008ed604:
      *(undefined1 *)(piVar6 + 6) = 1;
      *(undefined1 *)(iVar4 + 0x18) = 1;
      *(undefined1 *)(*(int *)(*piVar5 + 4) + 0x18) = 0;
      piVar7 = *(int **)(*piVar5 + 4);
    }
    cVar1 = *(char *)(piVar7[1] + 0x18);
  } while( true );
}