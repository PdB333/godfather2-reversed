// Xbox PDB: EARS_Apt_UIHud_HideCrewCSA
// FUNC_NAME: CSACrewComponent::hideCrewCSA
void CSACrewComponent::hideCrewCSA(void)
{
  // Calls a function to hide the crew CSA (likely a UI element or overlay)
  // The function signature appears to be: void FUN_005a04a0(const char* name, int param, void* data, int param2)
  // +0x00: name = "HideCrewCSA"
  // +0x04: param = 0
  // +0x08: data = &DAT_00d8a64c (some global data)
  // +0x0C: param2 = 0
  FUN_005a04a0("HideCrewCSA", 0, &DAT_00d8a64c, 0);
  return;
}