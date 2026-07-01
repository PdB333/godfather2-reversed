// FUNC_NAME: ZoneManager::loadZone
void __fastcall ZoneManager::loadZone(int thisPtr)
{
  int in_EAX;
  bool in_ZF;
  
  if (in_ZF) {
    FUN_0098f8c0(&stack0x00000004);
  }
  else if (in_EAX == 1) {
    FUN_0098f8f0(&stack0x00000004);
  }
  else {
    FUN_0098f850(&stack0x00000004);
  }
  *(undefined **)(thisPtr + 0x5c) = PTR_DAT_00e575fc;
  FUN_005a04a0("UpdateTrickleText");
  *(undefined **)(thisPtr + 0x5c) = PTR_DAT_00e575fc;
  return;
}