// FUNC_NAME: SimNpc::isSameCharacter
bool __thiscall SimNpc::isSameCharacter(int this, int otherCharacter)
{
  int iVar1;
  
  // Check if this NPC is a "generic" type (bit 3 of flags at +0x108)
  if ((*(uint *)(this + 0x108) >> 3 & 1) != 0) {
    // For generic NPCs, compare the character template ID
    iVar1 = FUN_0043b490(); // likely getCharacterTemplateId()
    return *(int *)(this + 0x150) == iVar1;
  }
  
  // For non-generic NPCs, compare the character's unique ID (4 ints at +0x20)
  // This is likely a GUID or hash stored across 4 fields
  if (((((int *)(otherCharacter + 0x20) != (int *)0x0) &&
       (*(int *)(otherCharacter + 0x20) == *(int *)(this + 0x58))) &&
      (*(int *)(otherCharacter + 0x24) == *(int *)(this + 0x5c))) &&
     ((*(int *)(otherCharacter + 0x28) == *(int *)(this + 0x60) &&
      (*(int *)(otherCharacter + 0x2c) == *(int *)(this + 100))))) {
    return true;
  }
  return false;
}