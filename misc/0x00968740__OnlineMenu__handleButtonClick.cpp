// FUNC_NAME: OnlineMenu::handleButtonClick
char __thiscall OnlineMenu::handleButtonClick(int this, byte *path, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6)
{
  byte bVar1;
  undefined4 uVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  char local_41;
  byte abStack_40 [64];
  
  local_41 = '\0';
  // Check if menu is disabled via global flag at DAT_0112982c + 0x48
  if (*(char *)(DAT_0112982c + 0x48) != '\0') {
    return '\0';
  }
  // Check for special button types: button_0 through button_5
  if ((*(int *)(this + 0xdc) == 0xb) &&
     (local_41 = (**(code **)(*(int *)(this + 0x570) + 4))
                           (path,param3,param4,param5,param6), local_41 != '\0')) {
    return local_41;
  }
  if ((*(int *)(this + 0xdc) == 6) &&
     (local_41 = (**(code **)(*(int *)(this + 0x378) + 0x58))
                           (path,param3,param4,param5,param6), local_41 != '\0')) {
    return local_41;
  }
  // Compare path with "/onli/buttons/button_0/button"
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = (byte *)"/onli/buttons/button_0/button";
  pbVar5 = path;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pbVar3 == *pbVar5;
    pbVar3 = pbVar3 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    uVar2 = FUN_00466860();
    goto LAB_00968abf;
  }
  // Compare path with "/onli/buttons/button_1/button"
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = (byte *)"/onli/buttons/button_1/button";
  pbVar5 = path;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pbVar3 == *pbVar5;
    pbVar3 = pbVar3 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar6);
  if (bVar6) {
LAB_00968828:
    uVar2 = FUN_00466840();
    goto LAB_00968abf;
  }
  // Compare path with "/onli/buttons/button_2/button"
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = (byte *)"/onli/buttons/button_2/button";
  pbVar5 = path;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pbVar3 == *pbVar5;
    pbVar3 = pbVar3 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar6);
  if (bVar6) {
LAB_0096884b:
    uVar2 = 0xc;
    goto LAB_00968abf;
  }
  // Compare path with "/onli/buttons/button_3/button"
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = (byte *)"/onli/buttons/button_3/button";
  pbVar5 = path;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pbVar3 == *pbVar5;
    pbVar3 = pbVar3 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    uVar2 = 0;
    goto LAB_00968abf;
  }
  // Compare path with "/onli/buttons/button_4/button"
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = (byte *)"/onli/buttons/button_4/button";
  pbVar5 = path;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pbVar3 == *pbVar5;
    pbVar3 = pbVar3 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar6);
  if (bVar6) {
    uVar2 = 2;
    goto LAB_00968abf;
  }
  // Compare path with "/onli/buttons/button_5/button"
  iVar4 = 0x1e;
  bVar6 = true;
  pbVar3 = (byte *)"/onli/buttons/button_5/button";
  pbVar5 = path;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar6 = *pbVar3 == *pbVar5;
    pbVar3 = pbVar3 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar6);
  if (bVar6) goto LAB_0096884b;
  // Build path for item hotspot: "/onli/mcMain/content_mc/item%d/item_hspt"
  FUN_00910160(abStack_40,"/onli/mcMain/content_mc/item%d/item_hspt",*(undefined4 *)(this + 0xc4));
  pbVar3 = abStack_40;
  pbVar5 = path;
  do {
    bVar1 = *pbVar3;
    bVar6 = bVar1 < *pbVar5;
    if (bVar1 != *pbVar5) {
LAB_009688d4:
      iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
      goto LAB_009688d9;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar3[1];
    bVar6 = bVar1 < pbVar5[1];
    if (bVar1 != pbVar5[1]) goto LAB_009688d4;
    pbVar3 = pbVar3 + 2;
    pbVar5 = pbVar5 + 2;
  } while (bVar1 != 0);
  iVar4 = 0;
LAB_009688d9:
  if (iVar4 == 0) goto LAB_00968828;
  // Build path for type left: "/onli/mcMain/content_mc/item%d/type_mc/type/type1_left"
  FUN_00910160(abStack_40,"/onli/mcMain/content_mc/item%d/type_mc/type/type1_left",
               *(undefined4 *)(this + 0xc4));
  pbVar3 = abStack_40;
  pbVar5 = path;
  do {
    bVar1 = *pbVar3;
    bVar6 = bVar1 < *pbVar5;
    if (bVar1 != *pbVar5) {
LAB_00968920:
      iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
      goto LAB_00968925;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar3[1];
    bVar6 = bVar1 < pbVar5[1];
    if (bVar1 != pbVar5[1]) goto LAB_00968920;
    pbVar3 = pbVar3 + 2;
    pbVar5 = pbVar5 + 2;
  } while (bVar1 != 0);
  iVar4 = 0;
LAB_00968925:
  if (iVar4 == 0) {
LAB_00968abd:
    uVar2 = 6;
  }
  else {
    // Build path for type right: "/onli/mcMain/content_mc/item%d/type_mc/type/type1_right"
    FUN_00910160(abStack_40,"/onli/mcMain/content_mc/item%d/type_mc/type/type1_right",
                 *(undefined4 *)(this + 0xc4));
    pbVar3 = abStack_40;
    pbVar5 = path;
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_00968970:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_00968975;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_00968970;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_00968975:
    if (iVar4 != 0) {
      // Build path for left arrow hotspot: "/onli/mcMain/content_mc/item%d/type_mc/type/leftArrow/hspt"
      FUN_00910160(abStack_40,"/onli/mcMain/content_mc/item%d/type_mc/type/leftArrow/hspt",
                   *(undefined4 *)(this + 0xc4));
      pbVar3 = abStack_40;
      pbVar5 = path;
      do {
        bVar1 = *pbVar3;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_009689c0:
          iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_009689c5;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_009689c0;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_009689c5:
      if (iVar4 == 0) goto LAB_00968abd;
      // Build path for right arrow hotspot: "/onli/mcMain/content_mc/item%d/type_mc/type/rightArrow/hspt"
      FUN_00910160(abStack_40,"/onli/mcMain/content_mc/item%d/type_mc/type/rightArrow/hspt",
                   *(undefined4 *)(this + 0xc4));
      pbVar3 = abStack_40;
      pbVar5 = path;
      do {
        bVar1 = *pbVar3;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_00968a10:
          iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_00968a15;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_00968a10;
        pbVar3 = pbVar3 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_00968a15:
      if (iVar4 != 0) {
        // Build path for tree option: "/onli/mcMain/tree_mc/tree/tree/option_%d"
        FUN_00910160(abStack_40,"/onli/mcMain/tree_mc/tree/tree/option_%d",
                     *(undefined4 *)(this + 0x2dc));
        pbVar3 = abStack_40;
        pbVar5 = path;
        do {
          bVar1 = *pbVar3;
          bVar6 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_00968a60:
            iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
            goto LAB_00968a65;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar6 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_00968a60;
          pbVar3 = pbVar3 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        iVar4 = 0;
LAB_00968a65:
        if (iVar4 == 0) goto LAB_00968828;
        // Compare path with "/onli/mcMain/content_mc/neutral_mc/player0/left_hotspot"
        iVar4 = 0x38;
        bVar6 = true;
        pbVar3 = (byte *)"/onli/mcMain/content_mc/neutral_mc/player0/left_hotspot";
        pbVar5 = path;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar6 = *pbVar3 == *pbVar5;
          pbVar3 = pbVar3 + 1;
          pbVar5 = pbVar5 + 1;
        } while (bVar6);
        if (bVar6) goto LAB_00968abd;
        // Compare path with "/onli/mcMain/content_mc/neutral_mc/player0/right_hotspot"
        iVar4 = 0x39;
        bVar6 = true;
        pbVar3 = (byte *)"/onli/mcMain/content_mc/neutral_mc/player0/right_hotspot";
        pbVar5 = path;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar6 = *pbVar3 == *pbVar5;
          pbVar3 = pbVar3 + 1;
          pbVar5 = pbVar5 + 1;
        } while (bVar6);
        if (!bVar6) {
          // Compare path with "/onli/mcMain/content_mc/team0_mc/player0/team/right"
          iVar4 = 0x34;
          bVar6 = true;
          pbVar3 = (byte *)"/onli/mcMain/content_mc/team0_mc/player0/team/right";
          pbVar5 = path;
          do {
            if (iVar4 == 0) break;
            iVar4 = iVar4 + -1;
            bVar6 = *pbVar3 == *pbVar5;
            pbVar3 = pbVar3 + 1;
            pbVar5 = pbVar5 + 1;
          } while (bVar6);
          if (!bVar6) {
            // Compare path with "/onli/mcMain/content_mc/team1_mc/player0/team/left"
            iVar4 = 0x33;
            bVar6 = true;
            pbVar3 = (byte *)"/onli/mcMain/content_mc/team1_mc/player0/team/left";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar6 = *pbVar3 == *path;
              pbVar3 = pbVar3 + 1;
              path = path + 1;
            } while (bVar6);
            if (!bVar6) {
              return local_41;
            }
            goto LAB_00968abd;
          }
        }
      }
    }
    uVar2 = 7;
  }
LAB_00968abf:
  FUN_005bf350(uVar2);
  return '\x01';
}