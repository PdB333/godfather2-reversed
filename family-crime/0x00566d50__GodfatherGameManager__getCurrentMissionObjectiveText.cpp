// FUNC_NAME: GodfatherGameManager::getCurrentMissionObjectiveText
undefined8 GodfatherGameManager::getCurrentMissionObjectiveText(void)

{
  int *piVar1;
  undefined8 uVar2;
  
  piVar1 = (int *)FUN_00ad8d40(); // Likely GodfatherGameManager::getInstance() or similar singleton access
  if (piVar1 != (int *)0x0) {
    piVar1 = (int *)(**(code **)(*piVar1 + 0x48))(); // Get current mission manager or state (vtable offset 0x48)
    if (piVar1 != (int *)0x0) {
      piVar1 = (int *)(**(code **)(*piVar1 + 0x28))(); // Get current objective from mission (vtable offset 0x28)
      if (piVar1 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00566d82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar2 = (**(code **)(*piVar1 + 8))(); // Get objective text string (vtable offset 0x8)
        return uVar2;
      }
    }
  }
  return 0;
}