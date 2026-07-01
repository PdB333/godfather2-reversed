// FUNC_NAME: NpcComponent::addSpecialties
void __thiscall NpcComponent::addSpecialties(int this, undefined4 specialtiesBitmask)
{
  *(undefined4 *)(this + 0x90) = specialtiesBitmask;  // +0x90: specialties bitmask
  if (*(char *)(this + 0x48) != '\0') {  // +0x48: some flag (initialized?)
    FUN_005a04a0("AddSpecialties", 0, &DAT_00d8b7d4, 0);  // likely a debug/log print
  }
  return;
}