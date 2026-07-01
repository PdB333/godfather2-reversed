// FUNC_NAME: NPCCrewComponent::updateCrewmateSelection
void NPCCrewComponent::updateCrewmateSelection(int param_1)
{
  int iVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint local_4;
  
  uVar7 = *(uint *)(param_1 + 0xc); // +0x0C: crewmateCount
  uVar8 = 0;
  if (uVar7 != 0) {
    do {
      iVar1 = *(int *)(param_1 + 8); // +0x08: crewmateArray (array of pointers)
      uVar5 = *(uint *)(iVar1 + uVar8 * 4); // current crewmate pointer
      if (*(char *)(uVar5 + 0x121) == '\0') { // +0x121: isActive flag
        local_4 = 0;
        bVar2 = false;
        uVar4 = -(uint)(uVar7 != 0) & uVar5;
        uVar6 = uVar8;
        while ((uVar3 = local_4, uVar4 != 0 && (uVar3 = uVar4, *(char *)(uVar4 + 0x121) != '\x01')))
        {
          if (uVar6 < uVar7 - 1) {
            uVar6 = uVar6 + 1;
          }
          else {
            uVar6 = 0;
          }
          if (uVar6 == uVar8) {
            bVar2 = true;
          }
          if ((uVar7 == 0) || (bVar2)) {
            uVar4 = 0;
          }
          else {
            uVar4 = *(uint *)(iVar1 + uVar6 * 4);
          }
        }
        local_4 = uVar3;
        bVar2 = false;
        uVar5 = -(uint)(uVar7 != 0) & uVar5;
        uVar4 = uVar8;
        while (uVar5 != 0) {
          if (*(char *)(uVar5 + 0x121) == '\x01') goto LAB_00822966;
          if (uVar4 == 0) {
            uVar4 = uVar7;
          }
          uVar4 = uVar4 - 1;
          if (uVar4 == uVar8) {
            bVar2 = true;
          }
          if ((uVar7 == 0) || (bVar2)) {
            uVar5 = 0;
          }
          else {
            uVar5 = *(uint *)(iVar1 + uVar4 * 4);
          }
        }
        uVar5 = 0;
LAB_00822966:
        if ((local_4 != 0) && (uVar5 != 0)) {
          FUN_00820590(uVar5,local_4); // likely assignCrewmateRole or swapCrewmate
        }
      }
      uVar7 = *(uint *)(param_1 + 0xc); // +0x0C: crewmateCount
      uVar8 = uVar8 + 1;
    } while (uVar8 < uVar7);
  }
  return;
}