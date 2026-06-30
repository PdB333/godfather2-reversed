// FUNC_NAME: RBTree::insert_node
void RBTree::insert_node(int param_1, int *param_2, char param_3)
{
  char cVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  undefined4 *unaff_EDI;
  undefined1 local_40 [4];
  uint local_3c;
  undefined4 local_2c;
  uint local_28;
  undefined **local_24;
  char *local_20;
  uint local_18;
  undefined4 local_8;
  uint local_4;
  
  // Check if tree size exceeds 0x1ffffffd (+0x20 is size field)
  if (0x1ffffffd < *(uint *)(param_1 + 0x20)) {
    // Throw exception: "map/set<T> too long"
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
  
  // Allocate new node (+0x1c is tree root/header, function returns new node)
  piVar3 = (int *)FUN_005e10f0(*(undefined4 *)(param_1 + 0x1c), unaff_EDI,
                               *(undefined4 *)(param_1 + 0x1c));
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1; // increment size
  
  // Insert node into tree
  if (unaff_EDI == *(undefined4 **)(param_1 + 0x1c)) {
    // First node - set as root
    (*(undefined4 **)(param_1 + 0x1c))[1] = (undefined4 *)piVar3;
    **(undefined4 **)(param_1 + 0x1c) = (undefined4 *)piVar3;
    *(int **)(*(int *)(param_1 + 0x1c) + 8) = piVar3;
  }
  else if (param_3 == '\\0') {
    // Insert as left child
    unaff_EDI[2] = (undefined4 *)piVar3;
    if (unaff_EDI == *(undefined4 **)(*(int *)(param_1 + 0x1c) + 8)) {
      *(int **)(*(int *)(param_1 + 0x1c) + 8) = piVar3;
    }
  }
  else {
    // Insert as right child
    *unaff_EDI = (undefined4 *)piVar3;
    if (unaff_EDI == (undefined4 *)**(int **)(param_1 + 0x1c)) {
      **(int **)(param_1 + 0x1c) = (int)piVar3;
    }
  }
  
  // Fix red-black tree balance
  cVar1 = *(char *)(piVar3[1] + 0x14); // parent's color (red/black, 0x14 is color field)
  piVar7 = piVar3;
  do {
    if (cVar1 != '\\0') { // if parent is red
      // Recolor and rotate as needed
      *(undefined1 *)(*(int *)(*(int *)(param_1 + 0x1c) + 4) + 0x14) = 1; // recolor uncle to black
      param_2[1] = (int)piVar3;
      *param_2 = param_1;
      return;
    }
    piVar4 = piVar7 + 1;
    piVar5 = (int *)*piVar4;
    piVar2 = (int *)piVar5[1];
    if (piVar5 == (int *)*piVar2) {
      iVar6 = piVar2[2];
      if (*(char *)(iVar6 + 0x14) == '\\0') goto LAB_005e071d;
      if (piVar7 == (int *)piVar5[2]) {
        piVar7 = (int *)piVar5[2];
        piVar5[2] = *piVar7;
        if (*(char *)(*piVar7 + 0x15) == '\\0') {
          *(int **)(*piVar7 + 4) = piVar5;
        }
        piVar4 = piVar5 + 1;
        piVar7[1] = piVar5[1];
        if (piVar5 == *(int **)(*(int *)(param_1 + 0x1c) + 4)) {
          *(int **)(*(int *)(param_1 + 0x1c) + 4) = piVar7;
        }
        else {
          piVar2 = (int *)*piVar4;
          if (piVar5 == (int *)*piVar2) {
            *piVar2 = (int)piVar7;
          }
          else {
            piVar2[2] = (int)piVar7;
          }
        }
        *piVar7 = (int)piVar5;
        *piVar4 = (int)piVar7;
        piVar7 = piVar5;
      }
      // Continue recoloring/rotating up the tree
      *(undefined1 *)(*piVar4 + 0x14) = 1;
      *(undefined1 *)(*(int *)(*piVar4 + 4) + 0x14) = 0;
      piVar4 = *(int **)(*piVar4 + 4);
      piVar5 = (int *)*piVar4;
      *piVar4 = piVar5[2];
      if (*(char *)(piVar5[2] + 0x15) == '\\0') {
        *(int **)(piVar5[2] + 4) = piVar4;
      }
      piVar5[1] = piVar4[1];
      if (piVar4 == *(int **)(*(int *)(param_1 + 0x1c) + 4)) {
        *(int **)(*(int *)(param_1 + 0x1c) + 4) = piVar5;
        piVar5[2] = (int)piVar4;
      }
      else {
        piVar2 = (int *)piVar4[1];
        if (piVar4 == (int *)piVar2[2]) {
          piVar2[2] = (int)piVar5;
          piVar5[2] = (int)piVar4;
        }
        else {
          *piVar2 = (int)piVar5;
          piVar5[2] = (int)piVar4;
        }
      }
LAB_005e078e:
      piVar4[1] = (int)piVar5;
    }
    else {
      iVar6 = *piVar2;
      if (*(char *)(iVar6 + 0x14) != '\\0') {
        if (piVar7 == (int *)*piVar5) {
          FUN_005e1050(param_1);
          piVar7 = piVar5;
        }
        *(undefined1 *)(piVar7[1] + 0x14) = 1;
        *(undefined1 *)(*(int *)(piVar7[1] + 4) + 0x14) = 0;
        piVar4 = *(int **)(piVar7[1] + 4);
        piVar5 = (int *)piVar4[2];
        piVar4[2] = *piVar5;
        if (*(char *)(*piVar5 + 0x15) == '\\0') {
          *(int **)(*piVar5 + 4) = piVar4;
        }
        piVar5[1] = piVar4[1];
        if (piVar4 == *(int **)(*(int *)(param_1 + 0x1c) + 4)) {
          *(int **)(*(int *)(param_1 + 0x1c) + 4) = piVar5;
        }
        else {
          piVar2 = (int *)piVar4[1];
          if (piVar4 == (int *)*piVar2) {
            *piVar2 = (int)piVar5;
          }
          else {
            piVar2[2] = (int)piVar5;
          }
        }
        *piVar5 = (int)piVar4;
        goto LAB_005e078e;
      }
LAB_005e071d:
      *(undefined1 *)(piVar5 + 5) = 1;
      *(undefined1 *)(iVar6 + 0x14) = 1;
      *(undefined1 *)(*(int *)(*piVar4 + 4) + 0x14) = 0;
      piVar7 = *(int **)(*piVar4 + 4);
    }
    cVar1 = *(char *)(piVar7[1] + 0x14);
  } while( true );
}