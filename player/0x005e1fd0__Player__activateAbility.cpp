// FUNC_NAME: Player::activateAbility
undefined4 Player::activateAbility(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int this;
  int abilityIndex;
  
  FUN_005dbc10(); // likely some engine init or check
  piVar1 = DAT_01223510; // global pointer to some manager or vtable
  if (*(char *)(this + 0x1744) != '\0') { // +0x1744: some flag (e.g., isAlive, isActive)
    iVar2 = 0;
    piVar3 = (int *)(this + 0x490); // +0x490: array of ability IDs (5 slots)
    do {
      if (abilityIndex == *piVar3) { // check if abilityIndex matches current slot
        if (iVar2 == -1) {
          return 0;
        }
        iVar2 = iVar2 * 0x4a4 + 4 + this; // compute offset into ability data array (0x4a4 per entry)
        *(undefined4 *)(iVar2 + 0x20c) = 0x32; // +0x20c: set some timer/cooldown to 50 (0x32)
        (**(code **)(*piVar1 + 0x9c))(*(undefined4 *)(iVar2 + 0x1cc),0x32); // call vtable function at +0x9c with ability data pointer and 50
        return 1;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 0x129; // advance to next ability ID slot (0x129 * 4 = 0x4a4 bytes)
    } while (iVar2 < 5);
  }
  return 0;
}