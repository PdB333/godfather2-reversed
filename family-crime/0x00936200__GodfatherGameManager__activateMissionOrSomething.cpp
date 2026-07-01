// FUNC_NAME: GodfatherGameManager::activateMissionOrSomething
void __thiscall GodfatherGameManager::activateMissionOrSomething(int *this, undefined4 param_2, undefined1 param_3)
{
  char cVar1;
  int *piVar2;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  char *pcStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined1 *puStack_150;
  undefined4 uStack_14c;
  undefined1 auStack_140 [64];
  undefined1 auStack_100 [256];
  
  if (DAT_012234b8 != 0) {
    cVar1 = FUN_00566920(); // likely some check (e.g., isGameActive)
    if (cVar1 != '\0') {
      piVar2 = (int *)FUN_00ad8d40(); // likely getGameManager or similar
      if (piVar2 != (int *)0x0) {
        (**(code **)(*this + 0xc))(); // call virtual function at +0xC (maybe init?)
        piVar2 = (int *)(**(code **)(*piVar2 + 4))(); // get something from game manager
        FUN_00ae9750(); // likely string copy or format
        // Build a structure on stack for a timer or event
        pcStack_160 = "ACTIVE";
        uStack_164 = 1;
        uStack_168 = 0;
        uStack_16c = 0;
        uStack_170 = 0;
        DAT_011305ac = param_3; // store param_3 in global
        uStack_174 = 0;
        (**(code **)(*piVar2 + 0x40))(auStack_140,0); // call virtual at +0x40 (maybe setTimer)
        piVar2 = (int *)(**(code **)*piVar2)(); // get something else
        (**(code **)(*piVar2 + 0x10))(&uStack_174,FUN_00935580,&DAT_011305ac,10000); // schedule callback after 10 seconds
        this[0x25] = (int)pcStack_160; // set state string to "ACTIVE"
        FUN_00ae97f0(); // cleanup
        return;
      }
    }
  }
  FUN_00982c90(); // fallback/error handler
  return;
}