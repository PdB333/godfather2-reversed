// FUNC_NAME: CrewComponent::destroyCrewWeapons

void __thiscall CrewComponent::destroyCrewWeapons(CrewComponent* this, char forceDestroy)
{
  // Global crew data pointer (probably from a singleton)
  CrewData* crewData = g_crewData;
  uint* flags;

  // Debug logging
  FUN_005a04a0("DestroyCrewWeapons", 0, &DAT_00d8cdec, 0);

  // If forceDestroy is true and there is global crew data with at least one weapon pointer non‑null
  if ((((forceDestroy != '\0') && (g_crewManager != 0)) &&
      (*(int*)(g_crewManager + 0x28) != 0 || *(int*)(g_crewManager + 0x2c) != 0)) &&
     ((undefined4*)(g_crewManager + 0x28) != (undefined4*)0x0)) {
    // Clear the two weapon pointers (primary and secondary?)
    *(undefined4*)(g_crewManager + 0x28) = 0;  // +0x28 weapon slot A
    *(undefined4*)(g_crewManager + 0x2c) = 0;  // +0x2c weapon slot B
    g_crewWeaponsDestroyed = 0;                 // global flag: weapons destroyed
  }

  // Dispatch based on current state (enum stored at +0x18)
  switch(*(int*)(this + 0x18)) {
  case 0: // Idle / ready to destroy
    FUN_0096a2f0();  // playDestroyAnimation?
    break;
  case 5: // special state 5
    flags = (uint*)(crewData + 0x6f4);
    *flags = *flags | 4;                 // set bit2 (maybe "weapons destroyed" flag)
    FUN_00969720();                      // additional cleanup
    FUN_00402050(&g_taskFlag, 0);        // reset task flag (e.g., mission complete)
    return;
  case 6: // state 6
    FUN_00965ea0();                      // special destroy sequence
    FUN_00402050(&g_taskFlag, 0);
    return;
  case 7: // state 7
    flags = (uint*)(crewData + 0x6f4);
    *flags = *flags | 4;                 // same flag
    FUN_0096cd00();                      // another destroy variant
    FUN_00402050(&g_taskFlag, 0);
    return;
  }

  // Default cleanup (for all other states)
  FUN_00402050(&g_taskFlag, 0);
}