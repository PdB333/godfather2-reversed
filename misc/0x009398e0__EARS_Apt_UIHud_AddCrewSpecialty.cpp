// Xbox PDB: EARS_Apt_UIHud_AddCrewSpecialty
// FUNC_NAME: NPCCrewComponent::addCrewSpecialty
void __thiscall NPCCrewComponent::addCrewSpecialty(int thisPtr, undefined4 param_2, undefined4 specialtyId)
{
  int iVar1;
  
  // Check if the crew component is active (likely a flag at +0x48)
  if (*(char *)(thisPtr + 0x48) != '\0') {
    // Get some game object (likely the NPC's entity or crew leader)
    iVar1 = FUN_007351c0(); // Probably EntityManager::getEntity or similar
    if (iVar1 != 0) {
      // Get another reference (maybe crew leader or family data)
      iVar1 = FUN_007351c0(); // Same function called again
      // Copy a value from the source object's +0xC4 to this crew component's +0x70
      // +0x70 likely stores the crew specialty type or related data
      *(undefined4 *)(thisPtr + 0x70) = *(undefined4 *)(iVar1 + 0xc4);
    }
    // Store the specialty ID at +0x7C
    *(undefined4 *)(thisPtr + 0x7c) = specialtyId;
    // Log the action: "AddCrewSpecialty" with some debug data
    FUN_005a04a0("AddCrewSpecialty", 0, &DAT_00d8a64c, 0); // Likely Debug::log or similar
  }
  return;
}