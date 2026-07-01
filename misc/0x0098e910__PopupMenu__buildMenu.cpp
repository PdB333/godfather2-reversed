// FUNC_NAME: PopupMenu::buildMenu
void __fastcall PopupMenu::buildMenu(int this)
{
  int iVar1;
  undefined1 *puVar2;
  undefined2 **ppuVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  undefined2 *puVar8;
  undefined1 *puVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  undefined2 *local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  code *local_cc;
  undefined4 uStack_c8;
  undefined1 auStack_c4 [4];
  undefined1 auStack_c0 [96];
  undefined1 auStack_60 [96];
  
  // Clear the popup menu
  FUN_005a04a0("Clear",0,&DAT_00e3d7ac,0);
  uVar10 = 0;
  if (*(int *)(this + 0x74) != 0) {
    iVar11 = 0;
    do {
      // Set item index
      *(uint *)(*(int *)(this + 0x70) + 0x40 + iVar11) = uVar10;
      iVar1 = *(int *)(this + 0x70) + iVar11;
      *(undefined4 *)(this + 0x94) = *(undefined4 *)(*(int *)(this + 0x70) + 0x40 + iVar11);
      FUN_004d3b50(iVar1 + 0x10);
      if (*(int *)(iVar1 + 0x48) == 7) {
        if (local_d8 != (undefined2 *)0x0) {
          (*local_cc)(local_d8);
        }
        local_d8 = (undefined2 *)0x0;
        local_d0 = 0;
        local_d4 = 0;
        FUN_004d4060(*(undefined4 *)(iVar1 + 0x14),0x2a);
      }
      puVar8 = local_d8;
      if (local_d8 == (undefined2 *)0x0) {
        puVar8 = (undefined2 *)&DAT_0120546e;
      }
      puVar2 = *(undefined1 **)(*(int *)(this + 0x70) + iVar11);
      if (puVar2 == (undefined1 *)0x0) {
        puVar2 = &DAT_0120546e;
      }
      FUN_005a04a0("AddInputTextfield",0,&DAT_00e3d7ac,2,puVar2,puVar8);
      if (local_d8 != (undefined2 *)0x0) {
        (*local_cc)(local_d8);
      }
      uVar10 = uVar10 + 1;
      iVar11 = iVar11 + 0x4c;
    } while (uVar10 < *(uint *)(this + 0x74));
  }
  iVar11 = 0;
  uVar12 = 0;
  *(undefined4 *)(this + 0x94) = 0;
  if (*(int *)(this + 0x80) != 0) {
    do {
      puVar2 = *(undefined1 **)(*(int *)(this + 0x7c) + iVar11);
      if (puVar2 == (undefined1 *)0x0) {
        puVar2 = &DAT_0120546e;
      }
      FUN_005a04a0("AddButton",0,&DAT_00e3d7ac,1,puVar2);
      *(uint *)(iVar11 + 0x10 + *(int *)(this + 0x7c)) = uVar10;
      uVar12 = uVar12 + 1;
      iVar11 = iVar11 + 0x14;
      uVar10 = uVar10 + 1;
    } while (uVar12 < *(uint *)(this + 0x80));
  }
  uVar10 = 0;
  if (*(int *)(this + 0x74) != 0) {
    iVar11 = 0;
    do {
      if (*(int *)(*(int *)(this + 0x70) + 0x48 + iVar11) == 7) {
        FUN_0098d7a0(auStack_c0,"/text/popup_root/popup/contentPlaceholderMc/item%d",uVar10);
        FUN_0098cae0(auStack_c0);
      }
      else if (*(int *)(*(int *)(this + 0x70) + iVar11 + 0x14) != 0) {
        FUN_0098d7a0(auStack_c0,"/text/popup_root/popup/contentPlaceholderMc/item%d/instance8/input"
                     ,uVar10);
        puVar2 = *(undefined1 **)(*(int *)(this + 0x70) + 0x10 + iVar11);
        if (puVar2 == (undefined1 *)0x0) {
          puVar2 = &DAT_0120546e;
        }
        FUN_004dba80(puVar2,*(undefined4 *)(*(int *)(this + 0x70) + 0x14 + iVar11));
        uStack_c8 = FUN_004dafd0(auStack_c0);
        ppuVar3 = (undefined2 **)FUN_0098cd30(&uStack_c8);
        if (ppuVar3 != &local_d8) {
          puVar8 = local_d8;
          if (local_d8 == (undefined2 *)0x0) {
            puVar8 = &DAT_00e2df14;
          }
          FUN_004dbb10(puVar8,0,local_d4);
        }
        if (local_d8 != (undefined2 *)0x0) {
          (*local_cc)(local_d8);
        }
      }
      uVar10 = uVar10 + 1;
      iVar11 = iVar11 + 0x4c;
    } while (uVar10 < *(uint *)(this + 0x74));
  }
  uVar10 = *(uint *)(this + 0x74);
  if (uVar10 < *(int *)(this + 0x80) + uVar10) {
    do {
      FUN_0098d7a0(auStack_c0,"/text/popup_root/popup/contentPlaceholderMc/item%d/instance3",uVar10)
      ;
      FUN_0098ca70(auStack_c0);
      uVar10 = uVar10 + 1;
    } while (uVar10 < (uint)(*(int *)(this + 0x80) + *(int *)(this + 0x74)));
  }
  uVar10 = 0;
  if (*(int *)(this + 0x74) != 0) {
    piVar4 = (int *)(*(int *)(this + 0x70) + 0x14);
    do {
      if (*piVar4 == 0) {
        FUN_0098d7a0(auStack_c0,"/text/popup_root/popup/contentPlaceholderMc/item%d/instance8/input"
                     ,uVar10);
        FUN_0098d7a0(auStack_60,
                     "/text/popup_root/popup/contentPlaceholderMc/item%d/instance8/hotspot",uVar10);
        iVar11 = DAT_0112a044;
        FUN_004d3d90(auStack_c0);
        uVar5 = FUN_004dafd0(auStack_60);
        *(undefined4 *)(iVar11 + 0x270) = uVar5;
        break;
      }
      uVar10 = uVar10 + 1;
      piVar4 = piVar4 + 0x13;
    } while (uVar10 < *(uint *)(this + 0x74));
  }
  puVar6 = (undefined4 *)FUN_004d3b00(*(undefined4 *)(this + 0x88));
  puVar2 = (undefined1 *)*puVar6;
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e;
  }
  puVar9 = *(undefined1 **)(this + 0x60);
  if (puVar9 == (undefined1 *)0x0) {
    puVar9 = &DAT_0120546e;
  }
  puVar7 = *(undefined1 **)(this + 0x50);
  if (puVar7 == (undefined1 *)0x0) {
    puVar7 = &DAT_0120546e;
  }
  FUN_005a04a0("ShowPopup",0,&DAT_00e3d7ac,3,puVar7,puVar9,puVar2);
  if (local_d8 != (undefined2 *)0x0) {
    (*local_cc)(local_d8);
  }
  FUN_00910180(auStack_c4,&DAT_00e3266c,*(undefined4 *)(this + 0x74));
  FUN_005a04a0("ChangeFormOptionSelection",0,&DAT_00e3d7ac,1,auStack_c4);
  if (*(int *)(this + 0x80) == 0) {
    FUN_005a04a0("ActivateButton",0,&DAT_00e3d7ac,1,&DAT_00e36da0);
  }
  return;
}