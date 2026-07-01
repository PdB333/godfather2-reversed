// FUNC_NAME: MobFaceManager::handleButtonClick
undefined1 __thiscall MobFaceManager::handleButtonClick(int this, byte *buttonPath)
{
  byte bVar1;
  undefined4 buttonId;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  undefined1 local_4d;
  undefined4 local_4c;
  undefined4 local_48;
  undefined1 local_44;
  byte local_40 [64];
  
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = (byte *)"/mobf/buttons/button_0/button";
  pbVar5 = buttonPath;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pbVar3 == *pbVar5;
    pbVar3 = pbVar3 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar6);
  local_4d = 0;
  if (bVar6) {
    buttonId = FUN_00466860(); // getButtonId for button_0
  }
  else {
    iVar4 = 0x1e;
    bVar6 = true;
    pbVar3 = (byte *)"/mobf/buttons/button_1/button";
    pbVar5 = buttonPath;
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar6 = *pbVar3 == *pbVar5;
      pbVar3 = pbVar3 + 1;
      pbVar5 = pbVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      buttonId = 2;
    }
    else {
      iVar4 = 0x1e;
      bVar6 = true;
      pbVar3 = (byte *)"/mobf/buttons/button_2/button";
      pbVar5 = buttonPath;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar6 = *pbVar3 == *pbVar5;
        pbVar3 = pbVar3 + 1;
        pbVar5 = pbVar5 + 1;
      } while (bVar6);
      if (bVar6) {
        buttonId = 0;
      }
      else {
        iVar4 = 0x1e;
        bVar6 = true;
        pbVar3 = (byte *)"/mobf/buttons/button_3/button";
        pbVar5 = buttonPath;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar6 = *pbVar3 == *pbVar5;
          pbVar3 = pbVar3 + 1;
          pbVar5 = pbVar5 + 1;
        } while (bVar6);
        if (bVar6) {
          buttonId = 10;
        }
        else {
          FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/item_hspt",
                       *(undefined4 *)(this + 0x2b0)); // currentItemIndex
          pbVar3 = local_40;
          pbVar5 = buttonPath;
          do {
            bVar1 = *pbVar3;
            bVar6 = bVar1 < *pbVar5;
            if (bVar1 != *pbVar5) {
LAB_00959940:
              iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
              goto LAB_00959945;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar3[1];
            bVar6 = bVar1 < pbVar5[1];
            if (bVar1 != pbVar5[1]) goto LAB_00959940;
            pbVar3 = pbVar3 + 2;
            pbVar5 = pbVar5 + 2;
          } while (bVar1 != 0);
          iVar4 = 0;
LAB_00959945:
          if (iVar4 == 0) {
            buttonId = FUN_00466840(); // getItemHotspotId
          }
          else {
            FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/type_mc/type/selector_left",
                         *(undefined4 *)(this + 0x2b0)); // currentItemIndex
            pbVar3 = local_40;
            pbVar5 = buttonPath;
            do {
              bVar1 = *pbVar3;
              bVar6 = bVar1 < *pbVar5;
              if (bVar1 != *pbVar5) {
LAB_009599a0:
                iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
                goto LAB_009599a5;
              }
              if (bVar1 == 0) break;
              bVar1 = pbVar3[1];
              bVar6 = bVar1 < pbVar5[1];
              if (bVar1 != pbVar5[1]) goto LAB_009599a0;
              pbVar3 = pbVar3 + 2;
              pbVar5 = pbVar5 + 2;
            } while (bVar1 != 0);
            iVar4 = 0;
LAB_009599a5:
            if (iVar4 == 0) {
              buttonId = 6;
            }
            else {
              FUN_00910160(local_40,"/mobf/mcMain/menu_mc/item%d/type_mc/type/selector_right",
                           *(undefined4 *)(this + 0x2b0)); // currentItemIndex
              pbVar3 = local_40;
              do {
                bVar1 = *pbVar3;
                bVar6 = bVar1 < *buttonPath;
                if (bVar1 != *buttonPath) {
LAB_009599f0:
                  iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
                  goto LAB_009599f5;
                }
                if (bVar1 == 0) break;
                bVar1 = pbVar3[1];
                bVar6 = bVar1 < buttonPath[1];
                if (bVar1 != buttonPath[1]) goto LAB_009599f0;
                pbVar3 = pbVar3 + 2;
                buttonPath = buttonPath + 2;
              } while (bVar1 != 0);
              iVar4 = 0;
LAB_009599f5:
              if (iVar4 != 0) goto LAB_00959a08;
              buttonId = 7;
            }
          }
        }
      }
    }
  }
  FUN_005bf350(buttonId); // handleButtonAction
  local_4d = 1;
LAB_00959a08:
  if (*(char *)(this + 0x2ad) != '\0') { // isDirty flag
    local_4c = DAT_011302e8;
    local_48 = 0;
    local_44 = 0;
    FUN_00408a00(&local_4c,0); // some cleanup
    iVar4 = DAT_01129a74;
    if (*(char *)(this + 0x2ad) != '\0') {
      *(undefined4 *)(this + 0x2b4) = 0; // reset some state
      FUN_00926890(0,0,0,0,0); // refreshUI
      *(undefined1 *)(iVar4 + 0x3a3) = 1; // set some global flag
      *(undefined1 *)(this + 0x2ad) = 0; // clear dirty flag
    }
  }
  return local_4d;
}