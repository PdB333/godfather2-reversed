// FUNC_NAME: SaveManager::applySaveActions
void __thiscall SaveManager::applySaveActions(int *thisPtr, undefined4 stream)
{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 **ppuVar7;
  uint uVar8;
  undefined4 **ppuVar9;
  bool bVar10;
  char local_68;
  int iStack_64;
  undefined4 *puStack_60;
  uint local_5c;
  uint local_58;
  undefined4 *local_54;
  undefined2 uStack_50;
  undefined4 local_4c;
  undefined4 **local_c;
  
  FUN_0046f160(stream);
  FUN_0043aff0(stream, 0xae986323);
  ppuVar9 = local_c;
  uVar8 = local_5c;
  while( true ) {
    if (local_68 == '\0') {
      bVar10 = *ppuVar9 == (undefined4 *)0x0;
    }
    else {
      bVar10 = uVar8 == local_58;
    }
    if (bVar10) break;
    ppuVar7 = &local_54;
    if (local_68 == '\0') {
      ppuVar7 = ppuVar9;
    }
    if (*(short *)((int)ppuVar7 + 6) == 0x25e3) {
      puVar6 = (undefined4 *)(uint)*(ushort *)(ppuVar7 + 1);
    }
    else {
      puVar6 = ppuVar7[1];
    }
    if (puVar6 == (undefined4 *)0x0) {
      ppuVar7 = &local_54;
      if (local_68 == '\0') {
        ppuVar7 = ppuVar9;
      }
      if (((uint)ppuVar7[2] & 1) == 0) {
        // +0x184: flags, clear bit 7 (0x80)
        thisPtr[0x61] = thisPtr[0x61] & 0xffffff7f;
      }
      else {
        // +0x184: flags, set bit 7 (0x80)
        thisPtr[0x61] = thisPtr[0x61] | 0x80;
      }
    }
    else if (puVar6 == (undefined4 *)0x1) {
      if (local_68 != '\0') {
        ppuVar9 = &local_54;
      }
      if (*(short *)((int)ppuVar9 + 6) == 0x25e3) {
        if (*ppuVar9 == (undefined4 *)0x0) {
          ppuVar9 = (undefined4 **)&DAT_00e2a89b;
        }
        else {
          ppuVar9 = (undefined4 **)((int)ppuVar9[2] + (int)*ppuVar9);
        }
      }
      else {
        ppuVar9 = ppuVar9 + 2;
      }
      cVar2 = '\0';
      // +0x218: pointer to some sub-object, check +0x70 validity
      if (((ppuVar9 != (undefined4 **)0x0) && (thisPtr[0x86] != 0)) &&
         (cVar2 = '\0', *(int *)(thisPtr[0x86] + 0x70) != 0)) {
        uVar3 = FUN_004dafd0(ppuVar9);
        cVar1 = FUN_00573440();
        if (cVar1 != '\0') {
          // vtable +0x14c: virtual method for processing
          cVar2 = (**(code **)(*thisPtr + 0x14c))(uVar3, 0, 0);
        }
      }
      // vtable +0x180: virtual method for finalization, negate condition
      (**(code **)(*thisPtr + 0x180))(-(uint)(cVar2 != '\0') & (uint)ppuVar9);
      ppuVar9 = local_c;
      if (cVar2 == '\0') {
        // +0x184: clear bit 3 (0x08)
        thisPtr[0x61] = thisPtr[0x61] & 0xfffffff7;
        uVar8 = local_5c;
      }
      else {
        // +0x184: set bit 3 (0x08)
        thisPtr[0x61] = thisPtr[0x61] | 8;
        uVar8 = local_5c;
      }
    }
    if (local_68 == '\0') {
      if ((int)uVar8 < 0) {
        local_c = (undefined4 **)((int)ppuVar9 + (int)*ppuVar9);
        FUN_0043b140();
        ppuVar9 = local_c;
        uVar8 = local_5c;
      }
      else if ((int)uVar8 < (int)(local_58 - 1)) {
        local_5c = uVar8 + 1;
        local_c = (undefined4 **)((int)ppuVar9 + (int)*ppuVar9);
        ppuVar9 = (undefined4 **)((int)ppuVar9 + (int)*ppuVar9);
        uVar8 = local_5c;
      }
      else {
        local_c = (undefined4 **)&DAT_01163cf8;
        ppuVar9 = (undefined4 **)&DAT_01163cf8;
      }
    }
    else {
      local_5c = uVar8 + 1;
      uVar8 = local_5c;
      if (local_5c != local_58) {
        uStack_50 = (short)local_5c;
        if ((*(byte *)((local_5c >> 3) + iStack_64) & (byte)(1 << ((byte)local_5c & 7))) == 0) {
          local_4c = *puStack_60;
          local_54 = puStack_60;
          puStack_60 = puStack_60 + 1;
        }
        else {
          local_54 = (undefined4 *)0x0;
          local_4c = 0;
        }
      }
    }
  }
  piVar4 = (int *)FUN_0045d9e0(stream);
  // +0x277: boolean flag
  if (((*(char *)((int)thisPtr + 0x277) != '\0') && (piVar4 != (int *)0x0)) &&
     ((*piVar4 != 0 || (((piVar4[1] != 0 || (piVar4[2] != 0)) || (piVar4[3] != 0)))))) {
    FUN_00401f40(piVar4);
    iVar5 = FUN_004059b0(stream);
    if (iVar5 != 0) {
      // +0x290: store result, then copy to +0x3C (thisPtr+0xf)
      thisPtr[0xa4] = iVar5;
      FUN_004035c0(iVar5, 0x10, thisPtr + 0xf);
    }
  }
  return;
}