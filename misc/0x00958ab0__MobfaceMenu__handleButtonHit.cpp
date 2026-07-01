// FUNC_NAME: MobfaceMenu::handleButtonHit
bool __thiscall MobfaceMenu::handleButtonHit(int this, byte *buttonName)
{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  undefined4 local_4c;
  int local_48;
  undefined1 local_44;
  byte local_40 [64];
  
  pbVar2 = buttonName;
  bVar8 = false;
  uVar6 = 0;
  do {
    if (5 < uVar6) break;
    FUN_005c4630(local_40,0x40,"/mobf/buttons/button_%d/button",uVar6);
    pbVar3 = local_40;
    pbVar5 = pbVar2;
    do {
      bVar1 = *pbVar3;
      bVar7 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_00958b07:
        iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_00958b0c;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar7 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_00958b07;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_00958b0c:
    if (iVar4 == 0) {
      local_4c = DAT_011301c0;
      local_44 = 0;
      local_48 = iVar4;
      FUN_00408a00(&local_4c,0);
      FUN_005c4630(local_40,0x40,&DAT_00e3266c,uVar6);
      FUN_005a04a0("RollOverButton",0,&DAT_00d8c478,1,local_40);
      bVar8 = true;
    }
    uVar6 = uVar6 + 1;
  } while (bVar8 == false);
  uVar6 = 0;
  do {
    if ((bVar8 != false) || (6 < uVar6)) {
      return bVar8;
    }
    FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/item_hspt",uVar6);
    pbVar3 = local_40;
    pbVar5 = pbVar2;
    do {
      bVar1 = *pbVar3;
      bVar8 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_00958bc0:
        iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
        goto LAB_00958bc5;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar8 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_00958bc0;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_00958bc5:
    bVar8 = iVar4 == 0;
    if (bVar8) {
LAB_00958da5:
      FUN_00910180(&buttonName,&DAT_00e3266c,uVar6);
      FUN_005a04a0("RollOverSelection",0,&DAT_00d8c478,1,&buttonName);
      *(uint *)(this + 0x2b0) = uVar6;
    }
    else {
      FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/type_mc/type/selector_hspt",uVar6);
      pbVar3 = local_40;
      pbVar5 = pbVar2;
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00958c10:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_00958c15;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00958c10;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00958c15:
      bVar8 = iVar4 == 0;
      if (bVar8) goto LAB_00958da5;
      FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/type_mc/type/selector_left",uVar6);
      pbVar3 = local_40;
      pbVar5 = pbVar2;
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00958c60:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_00958c65;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00958c60;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00958c65:
      bVar8 = iVar4 == 0;
      if (bVar8) goto LAB_00958da5;
      FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/type_mc/type/selector_right",uVar6);
      pbVar3 = local_40;
      pbVar5 = pbVar2;
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00958cb0:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_00958cb5;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00958cb0;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00958cb5:
      bVar8 = iVar4 == 0;
      if (bVar8) goto LAB_00958da5;
      FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/type_mc/type/1Dslider_hspt",uVar6);
      pbVar3 = local_40;
      pbVar5 = pbVar2;
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00958d00:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_00958d05;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00958d00;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00958d05:
      bVar8 = iVar4 == 0;
      if (bVar8) goto LAB_00958da5;
      FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/type_mc/type/1Dslider_left",uVar6);
      pbVar3 = local_40;
      pbVar5 = pbVar2;
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00958d50:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_00958d55;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00958d50;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00958d55:
      bVar8 = iVar4 == 0;
      if (bVar8) goto LAB_00958da5;
      FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/type_mc/type/1Dslider_right",uVar6);
      pbVar3 = local_40;
      pbVar5 = pbVar2;
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00958d97:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_00958d9c;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00958d97;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00958d9c:
      bVar8 = iVar4 == 0;
      if (bVar8) goto LAB_00958da5;
    }
    uVar6 = uVar6 + 1;
  } while( true );
}