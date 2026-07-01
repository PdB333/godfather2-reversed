// FUNC_NAME: CrewWeaponsWindow::handleHSPTEvent
char __thiscall CrewWeaponsWindow::handleHSPTEvent(int thisPtr, byte *hpspString)
{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  char result;
  uint index;
  bool bVar7;
  byte local_60 [96];
  
  result = '\0';
  index = 0;
  do {
    if (*(uint *)(thisPtr + 0x10) <= index) break;
    FUN_005c4630(local_60,0x60,
                 "/onli/mcMain/content_top_mc/crewWeaponsWindow/leftPlaceHolder/crewMember%d/hspt",
                 index);
    pbVar2 = local_60;
    pbVar4 = hpspString;
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_0096a911:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_0096a916;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar7 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_0096a911;
      pbVar2 = pbVar2 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_0096a916:
    if (iVar3 == 0) {
      if (*(int *)(thisPtr + 4) == 1) {
        FUN_0096a870(); // likely showCrewMemberHighlight or similar
      }
      result = '\x01';
    }
    index = index + 1;
  } while (result == '\0');
  index = 0;
  do {
    if ((result != '\0') || (*(uint *)(thisPtr + 0x14) <= index)) {
      return result;
    }
    FUN_005c4630(local_60,0x60,
                 "/onli/mcMain/content_top_mc/crewWeaponsWindow/rightPlaceHolder/weapon%d/hspt",
                 index);
    pbVar2 = local_60;
    pbVar4 = hpspString;
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_0096a976:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_0096a97b;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar2[1];
      bVar7 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_0096a976;
      pbVar2 = pbVar2 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_0096a97b:
    if (iVar3 == 0) {
      if (*(int *)(thisPtr + 4) == 0) {
        FUN_0096a810(); // likely showWeaponHighlight or similar
      }
      result = '\x01';
    }
    index = index + 1;
  } while( true );
}