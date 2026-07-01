// FUNC_NAME: FamilyManager::handleFamilyEvent
void __fastcall FamilyManager::handleFamilyEvent(int thisPtr)
{
  int eventType;
  int arg1;
  int arg2;
  int arg3;
  int argCount;
  int *args;
  int result;
  
  eventType = *(int *)(thisPtr + 0xb8); // +0xB8: currentEventType
  if (eventType == 0x12) { // FAMILY_EVENT_LEADER_KILLED
    arg1 = FUN_00907680(0x1b); // getEventParam(27)
    arg2 = FUN_00907680(0x1c); // getEventParam(28)
    argCount = 2;
  }
  else {
    if (eventType == 0x13) { // FAMILY_EVENT_MEMBER_KILLED
      arg1 = FUN_00907680(0x15); // getEventParam(21)
      arg2 = FUN_00907680(0xe);  // getEventParam(14)
      arg3 = FUN_00907680(0x12); // getEventParam(18)
      args = &arg1;
      argCount = 3;
      result = FUN_00916c70(DAT_00e54d0c); // getFamilyManager()
      FUN_00918b30(result, args, argCount, FUN_0091bc10); // processEvent
      return;
    }
    if (eventType == 0x14) { // FAMILY_EVENT_MEMBER_ARRESTED
      arg1 = FUN_00907680(0xc); // getEventParam(12)
      args = &arg1;
      argCount = 1;
      result = FUN_00916c70(DAT_00e54d0c); // getFamilyManager()
      FUN_00918b30(result, args, argCount, FUN_0091bc10); // processEvent
      return;
    }
    if (eventType == 0x15) { // FAMILY_EVENT_MEMBER_RELEASED
      arg1 = FUN_00907680(0xb); // getEventParam(11)
      argCount = 1;
    }
    else {
      if (eventType == 0x16) { // FAMILY_EVENT_TERRITORY_TAKEN
        arg1 = FUN_00907680(0x16); // getEventParam(22)
        arg2 = FUN_00907680(0xd);  // getEventParam(13)
        arg3 = FUN_00907680(0x14); // getEventParam(20)
        args = &arg1;
        argCount = 3;
        result = FUN_00916c70(DAT_00e54d0c); // getFamilyManager()
        FUN_00918b30(result, args, argCount, FUN_0091bc10); // processEvent
        return;
      }
      if (eventType == 0x17) { // FAMILY_EVENT_TERRITORY_LOST
        arg1 = FUN_00907680(0x17); // getEventParam(23)
        arg2 = FUN_00907680(10);   // getEventParam(10)
        arg3 = FUN_00907680(0x10); // getEventParam(16)
        args = &arg1;
        argCount = 3;
        result = FUN_00916c70(DAT_00e54d0c); // getFamilyManager()
        FUN_00918b30(result, args, argCount, FUN_0091bc10); // processEvent
        return;
      }
      if (eventType != 0x18) { // FAMILY_EVENT_BUSINESS_RAIDED
        return;
      }
      // FAMILY_EVENT_BUSINESS_RAIDED
      arg1 = FUN_00907680(0x18); // getEventParam(24)
      arg2 = FUN_00907680(0xf);  // getEventParam(15)
      arg3 = FUN_00907680(0x13); // getEventParam(19)
      argCount = 3;
    }
  }
  args = &arg1;
  result = FUN_00916c70(DAT_00e54d0c); // getFamilyManager()
  FUN_00918b30(result, args, argCount, FUN_0091bc10); // processEvent
  return;
}