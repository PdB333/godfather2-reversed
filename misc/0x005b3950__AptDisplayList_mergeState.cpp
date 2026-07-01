// Xbox PDB: AptDisplayList::mergeState
// FUNC_NAME: NetGhostManager::mergeGhostList
void __thiscall NetGhostManager::mergeGhostList(undefined4 *this, uint *ghostList, int param_3, undefined4 param_4)
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  undefined4 *puVar9;
  uint *puVar10;
  uint *puVar11;
  uint *puVar12;
  
  uVar1 = *ghostList;
  uVar6 = uVar1;
  puVar12 = *(uint **)(uVar1 + 0x60); // +0x60: next ghost in list
  puVar10 = *(uint **)*this;
  puVar11 = (uint *)(*(uint **)*this)[0x18]; // +0x18: some list head
joined_r0x005b3971:
  do {
    puVar4 = puVar11;
    if (puVar4 == (uint *)0x0) goto LAB_005b3da5;
    uVar2 = puVar4[0xc]; // +0x30: ghost ID or sequence number
    puVar11 = puVar12;
    if (0x3fff < (int)uVar2) break;
    if (puVar12 == (uint *)0x0) {
LAB_005b3c96:
      puVar11 = (uint *)puVar4[0x18]; // +0x60: next ghost
      if ((~(byte)(*puVar4 >> 0xf) & 1) == 0) {
        uVar2 = puVar4[0x15]; // +0x54: some flag
        if (uVar2 != 0) {
          cVar5 = FUN_005abd70(); // check if ghost is valid
          if (cVar5 == '\0') {
            cVar5 = FUN_0059c5c0(0); // check some condition
            if (cVar5 != '\0') {
              FUN_0059c3b0(); // update ghost state
              cVar5 = FUN_005a4140(); // check another condition
              if (cVar5 == '\0') {
                FUN_0059c3b0(); // update ghost state
                iVar7 = FUN_005a3f20(); // get some manager
                iVar7 = *(int *)(iVar7 + 0xc); // +0x0c: some offset
                goto LAB_005b3cfa;
              }
            }
            iVar7 = 0;
          }
          else {
            iVar7 = uVar2 + 4;
          }
LAB_005b3cfa:
          uVar6 = uVar1;
          if ((puVar4[0xd] != 0) && (puVar8 = (uint *)FUN_005bb150(iVar7), puVar8 == puVar4)) {
            FUN_005bad80(iVar7); // remove ghost reference
          }
        }
        FUN_005aa310(); // cleanup
      }
      goto joined_r0x005b3971;
    }
    uVar3 = puVar12[0xc]; // +0x30: ghost ID of next
    iVar7 = uVar3 - uVar2;
    if (uVar3 != uVar2) {
LAB_005b3c44:
      if (SBORROW4(uVar3,uVar2) == iVar7 < 0) goto LAB_005b3c96;
      do {
        puVar8 = puVar12;
        puVar12 = puVar8;
        puVar11 = puVar4;
        if ((int)puVar4[0xc] <= (int)puVar8[0xc]) break;
        uVar2 = puVar8[0x18]; // +0x60: next
        *(uint *)(uVar6 + 0x60) = uVar2; // update list
        if (uVar2 != 0) {
          *(uint *)(uVar2 + 0x5c) = uVar6; // +0x5c: prev
        }
        puVar10[0x18] = (uint)puVar8;
        puVar8[0x17] = (uint)puVar10; // +0x5c: prev
        puVar8[0x18] = (uint)puVar4;
        puVar4[0x17] = (uint)puVar8;
        if (puVar8[0xd] != 0) { // +0x34: some data
          FUN_005ba7d0(param_4,puVar8[0xd],puVar8); // update ghost data
        }
        puVar12 = *(uint **)(uVar6 + 0x60);
        puVar10 = puVar8;
      } while (puVar12 != (uint *)0x0);
      goto joined_r0x005b3971;
    }
    if ((puVar4[0x16] == 0) || (*(int *)(puVar12[0x16] + 4) != *(int *)(puVar4[0x16] + 4))) {
      uVar3 = puVar12[0xc];
      iVar7 = uVar3 - uVar2;
      goto LAB_005b3c44;
    }
    uVar6 = *puVar12 & 0x7fff;
    puVar10 = puVar4;
    if (((((*puVar12 & 0x8000) == 0) || ((uVar6 != 0xd && (uVar6 != 0x12)))) &&
        (cVar5 = FUN_0059c950(), cVar5 == '\0')) || (((*puVar4 ^ *puVar12) & 0x7fff) != 0)) {
LAB_005b3a02:
      if ((*puVar4 & 0x7fff) == 0x12) goto LAB_005b3a10;
      FUN_005aa3d0(puVar4); // update ghost state
      FUN_005a69f0(puVar4); // update ghost state
      FUN_005aab30(puVar4); // update ghost state
      puVar4[0x16] = puVar12[0x16]; // +0x58: copy some data
      FUN_0059c2e0(puVar4); // update ghost
      uVar6 = *puVar12;
      *puVar4 = *puVar4 & 0xffff7fff;
      if ((uVar6 & 0x8000) != 0) {
        *puVar4 = *puVar4 | 0x8000;
      }
      *(undefined8 *)(puVar4 + 0xe) = *(undefined8 *)(puVar12 + 0xe); // copy ghost data
      *(undefined8 *)(puVar4 + 0x10) = *(undefined8 *)(puVar12 + 0x10);
      *(undefined8 *)(puVar4 + 0x12) = *(undefined8 *)(puVar12 + 0x12);
      *(undefined8 *)(puVar4 + 4) = *(undefined8 *)(puVar12 + 4);
      *(undefined8 *)(puVar4 + 6) = *(undefined8 *)(puVar12 + 6);
      *(undefined8 *)(puVar4 + 8) = *(undefined8 *)(puVar12 + 8);
      *(undefined8 *)(puVar4 + 10) = *(undefined8 *)(puVar12 + 10);
      puVar4[0x14] = puVar12[0x14]; // +0x50: copy data
      puVar12[0x14] = 0;
      if (puVar4[0xd] != 0) { // +0x34: some data
        FUN_005bad80(param_4);
        (**(code **)(&DAT_0103aee0 + (*(uint *)puVar4[0xd] & 0x7fff) * 4))((uint *)puVar4[0xd]);
      }
      puVar4[0xd] = puVar12[0xd]; // +0x34: copy data
      if (puVar12[0xd] != 0) {
        FUN_005ba7d0(param_4,puVar12[0xd],puVar4); // update ghost data
        FUN_0059c690(); // update ghost
      }
      *(uint **)(DAT_0119a9cc + 0x1408 + *(int *)(DAT_0119a9cc + 0x1c08) * 4) = puVar4;
      FUN_0059c690(); // update ghost
      iVar7 = DAT_0119a9cc;
      *(int *)(DAT_0119a9cc + 0x1c08) = *(int *)(DAT_0119a9cc + 0x1c08) + 1;
      if (0x1ff < *(int *)(iVar7 + 0x1c08)) {
        FUN_0059bf00(); // handle overflow
      }
      iVar7 = FUN_005a3f20(); // get some manager
      if (**(int **)(iVar7 + 8) == 5) {
        iVar7 = 0;
        puVar9 = (undefined4 *)(DAT_0119a9cc + 0x1d14);
        do {
          if ((uint *)*puVar9 == puVar4) break;
          iVar7 = iVar7 + 1;
          puVar9 = puVar9 + 1;
        } while (iVar7 < 0x200);
      }
      puVar11 = (uint *)puVar12[0x18]; // +0x60: next
      *(uint **)(uVar1 + 0x60) = puVar11;
      if (puVar11 != (uint *)0x0) {
        puVar11[0x17] = uVar1; // +0x5c: prev
      }
      puVar12[0x18] = 0;
      puVar12[0x17] = 0;
      puVar12[0x16] = 0;
      FUN_005aa310(); // cleanup
    }
    else {
      if ((*(int *)(puVar12[0x16] + 8) != *(int *)(puVar4[0x16] + 8)) ||
         (*(int *)(puVar12[0x16] + 4) != *(int *)(puVar4[0x16] + 4))) goto LAB_005b3a02;
LAB_005b3a10:
      puVar11 = (uint *)puVar12[0x18]; // +0x60: next
      if ((char)puVar4[0x19] == '\0') { // +0x64: some flag
        *(undefined8 *)(puVar4 + 0xe) = *(undefined8 *)(puVar12 + 0xe); // copy ghost data
        *(undefined8 *)(puVar4 + 0x10) = *(undefined8 *)(puVar12 + 0x10);
        *(undefined8 *)(puVar4 + 0x12) = *(undefined8 *)(puVar12 + 0x12);
        *(undefined8 *)(puVar4 + 4) = *(undefined8 *)(puVar12 + 4);
        *(undefined8 *)(puVar4 + 6) = *(undefined8 *)(puVar12 + 6);
        *(undefined8 *)(puVar4 + 8) = *(undefined8 *)(puVar12 + 8);
        *(undefined8 *)(puVar4 + 10) = *(undefined8 *)(puVar12 + 10);
      }
      FUN_005b3030(); // update ghost
      if (puVar11 != (uint *)0x0) {
        uVar1 = puVar11[0x17]; // +0x5c: prev
        uVar6 = uVar1;
        puVar12 = puVar11;
        puVar11 = (uint *)puVar4[0x18]; // +0x60: next
        goto joined_r0x005b3971;
      }
    }
    uVar6 = uVar1;
    puVar12 = puVar11;
    puVar11 = (uint *)puVar4[0x18]; // +0x60: next
  } while( true );
joined_r0x005b3d2f:
  puVar12 = puVar11;
  if (puVar12 == (uint *)0x0) goto LAB_005b3dd0;
  if ((int)puVar4[0xc] <= (int)puVar12[0xc]) {
    FUN_0059bf00(); // handle overflow
LAB_005b3da5:
    if (puVar12 != (uint *)0x0) {
      *(undefined4 *)(uVar6 + 0x60) = 0;
      puVar10[0x18] = (uint)puVar12;
      puVar12[0x17] = (uint)puVar10; // +0x5c: prev
      do {
        if (puVar12[0xd] != 0) { // +0x34: some data
          FUN_005ba7d0(param_4,puVar12[0xd],puVar12); // update ghost data
        }
        puVar12 = (uint *)puVar12[0x18]; // +0x60: next
      } while (puVar12 != (uint *)0x0);
    }
LAB_005b3dd0:
    if (param_3 != 0) {
      FUN_005ba710(); // cleanup
      (*DAT_0119caf8)(param_3,0x48); // free memory
    }
    FUN_005b1e40(); // finalize
    (*DAT_0119caf8)(ghostList,4); // free memory
    return;
  }
  uVar1 = puVar12[0x18]; // +0x60: next
  *(uint *)(uVar6 + 0x60) = uVar1;
  if (uVar1 != 0) {
    *(uint *)(uVar1 + 0x5c) = uVar6; // +0x5c: prev
  }
  puVar10[0x18] = (uint)puVar12;
  puVar12[0x17] = (uint)puVar10; // +0x5c: prev
  puVar12[0x18] = (uint)puVar4;
  puVar4[0x17] = (uint)puVar12; // +0x5c: prev
  if (puVar12[0xd] != 0) { // +0x34: some data
    FUN_005ba7d0(param_4,puVar12[0xd],puVar12); // update ghost data
  }
  puVar11 = *(uint **)(uVar6 + 0x60);
  puVar10 = puVar12;
  goto joined_r0x005b3d2f;
}