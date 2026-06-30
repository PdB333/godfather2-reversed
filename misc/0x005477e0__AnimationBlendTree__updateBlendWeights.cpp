// FUNC_NAME: AnimationBlendTree::updateBlendWeights
void AnimationBlendTree::updateBlendWeights(undefined4 param_1, int *param_2)
{
  float *pfVar1;
  float fVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 **ppuVar7;
  int iVar8;
  char cVar9;
  int iVar10;
  int iVar11;
  int unaff_EDI;
  bool bVar12;
  char cStack_64;
  int iStack_60;
  undefined4 *puStack_5c;
  uint uStack_58;
  uint uStack_54;
  undefined4 *puStack_50;
  undefined2 uStack_4c;
  undefined4 uStack_48;
  undefined4 **ppuStack_8;
  
  iVar3 = (**(code **)(*param_2 + 0x220))(); // Get number of blend nodes
  FUN_0043aff0(param_1,0xe97cfb79); // Initialize iterator
  while( true ) {
    if (cStack_64 == '\0') {
      bVar12 = *ppuStack_8 == (undefined4 *)0x0;
    }
    else {
      bVar12 = uStack_58 == uStack_54;
    }
    if (bVar12) break;
    ppuVar7 = &puStack_50;
    if (cStack_64 == '\0') {
      ppuVar7 = ppuStack_8;
    }
    if (*(short *)((int)ppuVar7 + 6) == 0x25e3) {
      puVar4 = (undefined4 *)(uint)*(ushort *)(ppuVar7 + 1);
    }
    else {
      puVar4 = ppuVar7[1];
    }
    switch(puVar4) {
    case (undefined4 *)0x0: // Blend weight type 0
      cVar9 = '\0';
      if (0 < iVar3) {
        iVar11 = 0;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          cVar9 = cVar9 + '\x01';
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + iVar11 * 0x28) = ppuVar7[2]; // +0x8c: blend weights array
          iVar11 = (int)cVar9;
        } while (iVar11 < iVar3);
      }
      break;
    case (undefined4 *)0x1: // Blend weight type 1
      cVar9 = '\0';
      if (0 < iVar3) {
        iVar11 = 0;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          cVar9 = cVar9 + '\x01';
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 8 + iVar11 * 0x28) = ppuVar7[2]; // +8 offset for second weight
          iVar11 = (int)cVar9;
        } while (iVar11 < iVar3);
      }
      break;
    case (undefined4 *)0x2: // Blend weight type 2
      cVar9 = '\0';
      if (0 < iVar3) {
        iVar11 = 0;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          cVar9 = cVar9 + '\x01';
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 4 + iVar11 * 0x28) = ppuVar7[2]; // +4 offset for third weight
          iVar11 = (int)cVar9;
        } while (iVar11 < iVar3);
      }
      break;
    case (undefined4 *)0x3: // Blend weight type 3 - full 4-component set
      uVar6 = (**(code **)(*param_2 + 0x228))(0); // Get start index
      uVar5 = 0;
      if (3 < (int)uVar6) {
        iVar11 = 0;
        iVar8 = (uVar6 - 4 >> 2) + 1;
        uVar5 = iVar8 * 4;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0xc + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2]; // +0xc: weight 0
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x34 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2]; // +0x34: weight 1
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x5c + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2]; // +0x5c: weight 2
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x84 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2]; // +0x84: weight 3
          iVar11 = iVar11 + 0xa0;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      if (uVar5 < uVar6) {
        iVar11 = uVar5 * 0x28;
        iVar8 = uVar6 - uVar5;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0xc + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          iVar11 = iVar11 + 0x28;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      break;
    case (undefined4 *)0x4: // Blend weight type 4 - partial update from start
      uVar5 = (**(code **)(*param_2 + 0x228))(0);
      uVar6 = (**(code **)(*param_2 + 0x220))();
      if (3 < (int)(uVar6 - uVar5)) {
        iVar11 = uVar5 * 0x28;
        iVar8 = ((uVar6 - uVar5) - 4 >> 2) + 1;
        uVar5 = uVar5 + iVar8 * 4;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0xc + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x34 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x5c + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x84 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          iVar11 = iVar11 + 0xa0;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      if (uVar5 < uVar6) {
        iVar11 = uVar5 * 0x28;
        iVar8 = uVar6 - uVar5;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0xc + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          iVar11 = iVar11 + 0x28;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      break;
    case (undefined4 *)0x5: // Blend weight type 5 - different offset set
      uVar6 = (**(code **)(*param_2 + 0x228))(0);
      uVar5 = 0;
      if (3 < (int)uVar6) {
        iVar11 = 0;
        iVar8 = (uVar6 - 4 >> 2) + 1;
        uVar5 = iVar8 * 4;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x10 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2]; // +0x10: weight 0
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x38 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2]; // +0x38: weight 1
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x60 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2]; // +0x60: weight 2
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x88 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2]; // +0x88: weight 3
          iVar11 = iVar11 + 0xa0;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      if (uVar5 < uVar6) {
        iVar11 = uVar5 * 0x28;
        iVar8 = uVar6 - uVar5;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x10 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          iVar11 = iVar11 + 0x28;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      break;
    case (undefined4 *)0x6: // Blend weight type 6 - partial update from start with +0x10 offset
      uVar5 = (**(code **)(*param_2 + 0x228))(0);
      uVar6 = (**(code **)(*param_2 + 0x220))();
      if (3 < (int)(uVar6 - uVar5)) {
        iVar11 = uVar5 * 0x28;
        iVar8 = ((uVar6 - uVar5) - 4 >> 2) + 1;
        uVar5 = uVar5 + iVar8 * 4;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x10 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x38 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x60 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(iVar11 + 0x88 + *(int *)(unaff_EDI + 0x8c)) = ppuVar7[2];
          iVar11 = iVar11 + 0xa0;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      if (uVar5 < uVar6) {
        iVar11 = uVar5 * 0x28;
        iVar8 = uVar6 - uVar5;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x10 + iVar11) = ppuVar7[2];
          iVar11 = iVar11 + 0x28;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      break;
    case (undefined4 *)0x7: // Blend weight type 7 - different offset set
      uVar6 = (**(code **)(*param_2 + 0x228))(0);
      uVar5 = 0;
      if (3 < (int)uVar6) {
        iVar11 = 0;
        iVar8 = (uVar6 - 4 >> 2) + 1;
        uVar5 = iVar8 * 4;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar11) = ppuVar7[2]; // +0x14: weight 0
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x3c + iVar11) = ppuVar7[2]; // +0x3c: weight 1
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 100 + iVar11) = ppuVar7[2]; // +0x64: weight 2
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x8c + iVar11) = ppuVar7[2]; // +0x8c: weight 3
          iVar11 = iVar11 + 0xa0;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      if (uVar5 < uVar6) {
        iVar11 = uVar5 * 0x28;
        iVar8 = uVar6 - uVar5;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar11) = ppuVar7[2];
          iVar11 = iVar11 + 0x28;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      break;
    case (undefined4 *)0x8: // Blend weight type 8 - partial update from start with +0x14 offset
      uVar5 = (**(code **)(*param_2 + 0x228))(0);
      uVar6 = (**(code **)(*param_2 + 0x220))();
      if (3 < (int)(uVar6 - uVar5)) {
        iVar11 = uVar5 * 0x28;
        iVar8 = ((uVar6 - uVar5) - 4 >> 2) + 1;
        uVar5 = uVar5 + iVar8 * 4;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar11) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x3c + iVar11) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 100 + iVar11) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x8c + iVar11) = ppuVar7[2];
          iVar11 = iVar11 + 0xa0;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      if (uVar5 < uVar6) {
        iVar11 = uVar5 * 0x28;
        iVar8 = uVar6 - uVar5;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar11) = ppuVar7[2];
          iVar11 = iVar11 + 0x28;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      break;
    case (undefined4 *)0x9: // Blend weight type 9 - different offset set
      uVar6 = (**(code **)(*param_2 + 0x228))(0);
      uVar5 = 0;
      if (3 < (int)uVar6) {
        iVar11 = 0;
        iVar8 = (uVar6 - 4 >> 2) + 1;
        uVar5 = iVar8 * 4;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x1c + iVar11) = ppuVar7[2]; // +0x1c: weight 0
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x44 + iVar11) = ppuVar7[2]; // +0x44: weight 1
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x6c + iVar11) = ppuVar7[2]; // +0x6c: weight 2
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x94 + iVar11) = ppuVar7[2]; // +0x94: weight 3
          iVar11 = iVar11 + 0xa0;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      if (uVar5 < uVar6) {
        iVar11 = uVar5 * 0x28;
        iVar8 = uVar6 - uVar5;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x1c + iVar11) = ppuVar7[2];
          iVar11 = iVar11 + 0x28;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      break;
    case (undefined4 *)0xa: // Blend weight type 10 - partial update from start with +0x1c offset
      uVar5 = (**(code **)(*param_2 + 0x228))(0);
      uVar6 = (**(code **)(*param_2 + 0x220))();
      if (3 < (int)(uVar6 - uVar5)) {
        iVar11 = uVar5 * 0x28;
        iVar8 = ((uVar6 - uVar5) - 4 >> 2) + 1;
        uVar5 = uVar5 + iVar8 * 4;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x1c + iVar11) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x44 + iVar11) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x6c + iVar11) = ppuVar7[2];
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x94 + iVar11) = ppuVar7[2];
          iVar11 = iVar11 + 0xa0;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      if (uVar5 < uVar6) {
        iVar11 = uVar5 * 0x28;
        iVar8 = uVar6 - uVar5;
        do {
          ppuVar7 = &puStack_50;
          if (cStack_64 == '\0') {
            ppuVar7 = ppuStack_8;
          }
          *(undefined4 **)(*(int *)(unaff_EDI + 0x8c) + 0x1c + iVar11) = ppuVar7[2];
          iVar11 = iVar11 + 0x28;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
    }
    if (cStack_64 == '\0') {
      if ((int)uStack_58 < 0) {
        ppuStack_8 = (undefined4 **)((int)ppuStack_8 + (int)*ppuStack_8);
        FUN_0043b140();
      }
      else if ((int)uStack_58 < (int)(uStack_54 - 1)) {
        uStack_58 = uStack_58 + 1;
        ppuStack_8 = (undefined4 **)((int)ppuStack_8 + (int)*ppuStack_8);
      }
      else {
        ppuStack_8 = (undefined4 **)&DAT_01163cf8;
      }
    }
    else {
      uStack_58 = uStack_58 + 1;
      if (uStack_58 != uStack_54) {
        uStack_4c = (short)uStack_58;
        if ((*(byte *)((uStack_58 >> 3) + iStack_60) & (byte)(1 << ((byte)uStack_58 & 7))) == 0) {
          puStack_50 = puStack_5c;
          uStack_48 = *puStack_5c;
          puStack_5c = puStack_5c + 1;
        }
        else {
          puStack_50 = (undefined4 *)0x0;
          uStack_48 = 0;
        }
      }
    }
  }
  iVar11 = 0;
  if (3 < iVar3) {
    iVar8 = 0;
    iVar10 = (iVar3 - 4U >> 2) + 1;
    iVar11 = iVar10 * 4;
    do {
      fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0xc + iVar8);
      pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x14);
      if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
        *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0xc) =
             *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar8);
      }
      fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0x34 + iVar8);
      pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x3c);
      if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
        *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x34) =
             *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 0x3c + iVar8);
      }
      fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0x5c + iVar8);
      pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 100);
      if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
        *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x5c) =
             *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 100 + iVar8);
      }
      fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0x84 + iVar8);
      pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x8c);
      if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
        *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x84) =
             *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 0x8c + iVar8);
      }
      iVar8 = iVar8 + 0xa0;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
  }
  if (iVar11 < iVar3) {
    iVar8 = iVar11 * 0x28;
    iVar3 = iVar3 - iVar11;
    do {
      fVar2 = *(float *)(*(int *)(unaff_EDI + 0x8c) + 0xc + iVar8);
      pfVar1 = (float *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0x14);
      if (*pfVar1 <= fVar2 && fVar2 != *pfVar1) {
        *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + iVar8 + 0xc) =
             *(undefined4 *)(*(int *)(unaff_EDI + 0x8c) + 0x14 + iVar8);
      }
      iVar8 = iVar8 + 0x28;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}