// FUNC_NAME: RBTree::eraseNode
void __thiscall RBTree::eraseNode(int thisPtr, undefined4 *resultOut, undefined4 returnValue, int *nodeToErase)
{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  undefined1 local_40 [4];
  uint local_3c;
  undefined4 local_2c;
  uint local_28;
  undefined **local_24;
  char *local_20;
  uint local_18;
  undefined4 local_8;
  uint local_4;
  
  if (*(char *)((int)nodeToErase + 0x25) != '\0') {
    local_28 = 0xf;
    local_2c = 0;
    local_3c = local_3c & 0xffffff00;
    FUN_0043f9f0("invalid map/set<T> iterator",0x1b);
    local_20 = "unknown";
    local_24 = &PTR_FUN_00da9810;
    local_4 = 0xf;
    local_8 = 0;
    local_18 = local_18 & 0xffffff00;
    FUN_0043eeb0(local_40,0,0xffffffff);
    local_24 = &PTR_FUN_00da9834;
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
  FUN_006940f0();
  piVar6 = (int *)*nodeToErase;
  if (*(char *)((int)piVar6 + 0x25) == '\0') {
    if (*(char *)(nodeToErase[2] + 0x25) == '\0') {
      piVar6 = (int *)nodeToErase[2];
    }
  }
  else {
    piVar6 = (int *)nodeToErase[2];
  }
  piVar5 = (int *)nodeToErase[1];
  if (*(char *)((int)piVar6 + 0x25) == '\0') {
    piVar6[1] = (int)piVar5;
  }
  if (*(int **)(*(int *)(thisPtr + 4) + 4) == nodeToErase) {
    *(int **)(*(int *)(thisPtr + 4) + 4) = piVar6;
  }
  else if ((int *)*piVar5 == nodeToErase) {
    *piVar5 = (int)piVar6;
  }
  else {
    piVar5[2] = (int)piVar6;
  }
  puVar1 = *(undefined4 **)(thisPtr + 4);
  if ((int *)*puVar1 == nodeToErase) {
    piVar3 = piVar5;
    if (*(char *)((int)piVar6 + 0x25) == '\0') {
      piVar3 = (int *)FUN_00693fe0(piVar6);
    }
    *puVar1 = piVar3;
  }
  iVar2 = *(int *)(thisPtr + 4);
  if (*(int **)(iVar2 + 8) == nodeToErase) {
    if (*(char *)((int)piVar6 + 0x25) == '\0') {
      uVar4 = FUN_00693fc0(piVar6);
      *(undefined4 *)(iVar2 + 8) = uVar4;
    }
    else {
      *(int **)(iVar2 + 8) = piVar5;
    }
  }
  if ((char)nodeToErase[9] == '\x01') {
    if (piVar6 != *(int **)(*(int *)(thisPtr + 4) + 4)) {
      do {
        piVar3 = piVar5;
        if ((char)piVar6[9] != '\x01') break;
        piVar5 = (int *)*piVar3;
        if (piVar6 == piVar5) {
          piVar5 = (int *)piVar3[2];
          if ((char)piVar5[9] == '\0') {
            *(undefined1 *)(piVar5 + 9) = 1;
            *(undefined1 *)(piVar3 + 9) = 0;
            FUN_006949d0(piVar3);
            piVar5 = (int *)piVar3[2];
          }
          if (*(char *)((int)piVar5 + 0x25) == '\0') {
            if ((*(char *)(*piVar5 + 0x24) != '\x01') || (*(char *)(piVar5[2] + 0x24) != '\x01')) {
              if (*(char *)(piVar5[2] + 0x24) == '\x01') {
                *(undefined1 *)(*piVar5 + 0x24) = 1;
                *(undefined1 *)(piVar5 + 9) = 0;
                FUN_00693e70(piVar5);
                piVar5 = (int *)piVar3[2];
              }
              *(char *)(piVar5 + 9) = (char)piVar3[9];
              *(undefined1 *)(piVar3 + 9) = 1;
              *(undefined1 *)(piVar5[2] + 0x24) = 1;
              FUN_006949d0(piVar3);
              break;
            }
LAB_006959f4:
            *(undefined1 *)(piVar5 + 9) = 0;
          }
        }
        else {
          if ((char)piVar5[9] == '\0') {
            *(undefined1 *)(piVar5 + 9) = 1;
            *(undefined1 *)(piVar3 + 9) = 0;
            FUN_00693e70(piVar3);
            piVar5 = (int *)*piVar3;
          }
          if (*(char *)((int)piVar5 + 0x25) == '\0') {
            if ((*(char *)(piVar5[2] + 0x24) == '\x01') && (*(char *)(*piVar5 + 0x24) == '\x01'))
            goto LAB_006959f4;
            if (*(char *)(*piVar5 + 0x24) == '\x01') {
              *(undefined1 *)(piVar5[2] + 0x24) = 1;
              *(undefined1 *)(piVar5 + 9) = 0;
              FUN_006949d0(piVar5);
              piVar5 = (int *)*piVar3;
            }
            *(char *)(piVar5 + 9) = (char)piVar3[9];
            *(undefined1 *)(piVar3 + 9) = 1;
            *(undefined1 *)(*piVar5 + 0x24) = 1;
            FUN_00693e70(piVar3);
            break;
          }
        }
        piVar5 = (int *)piVar3[1];
        piVar6 = piVar3;
      } while (piVar3 != *(int **)(*(int *)(thisPtr + 4) + 4));
    }
    *(undefined1 *)(piVar6 + 9) = 1;
  }
  if (nodeToErase[3] != 0) {
    (*(code *)nodeToErase[6])(nodeToErase[3]);
  }
  FUN_009c8eb0(nodeToErase);
  if (*(int *)(thisPtr + 8) != 0) {
    *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + -1;
  }
  *resultOut = returnValue;
  resultOut[1] = nodeToErase;
  return;
}