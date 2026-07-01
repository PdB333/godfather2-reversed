// FUNC_NAME: MissionTypeSelector::constructor
void __thiscall MissionTypeSelector_constructor(int param_1, int missionType, int param_3, int param_4)
{
  *(int *)(param_1 + 8) = param_3;
  *(int *)(param_1 + 12) = param_4;
  *(int *)param_1 = 0xd68494; // vtable pointer
  *(int *)(param_1 + 4) = missionType;
  *(int *)(param_1 + 16) = 0; // subtitleType default

  switch(missionType) {
  case 0: // STORY_MISSION
  case 1: // SIDE_MISSION
  case 2: // FAVOR_MISSION
  case 3: // TUTORIAL_MISSION
    *(int *)(param_1 + 16) = 1; // subtitleType = MAIN_SUBTITLE
    return;
  case 4: // HIT_MISSION
  case 5: // CONTRACT_MISSION
  case 6: // EXTORTION_MISSION
  case 7: // TAKEOVER_MISSION
  case 8: // RIVAL_ATTACK_MISSION
  case 9: // PROTECTION_MISSION
  case 10: // ASSASSINATION_MISSION
  case 11: // CHASE_MISSION
    *(int *)(param_1 + 16) = 2; // subtitleType = SIDE_SUBTITLE
    return;
  case 12: // MONOPOLY_MISSION
    *(int *)(param_1 + 16) = 0; // subtitleType = NO_SUBTITLE
  }
}