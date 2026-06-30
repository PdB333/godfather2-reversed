// FUNC_NAME: Condition::matchesId
undefined4 __thiscall Condition::matchesId(uint *this, uint id) {
  int playerPtr;
  uint firstId;
  uint secondId;

  firstId = this[3];  // +0x0C: first optional id
  secondId = this[4]; // +0x10: second optional id

  // Check flag bits: bit0 = usePlayerFirstId, bit1 = usePlayerSecondId
  if ((*this & 1) != 0) {
    playerPtr = FUN_0078e110(); // getPlayer() or similar global singleton
    if (playerPtr != 0) {
      firstId = *(uint *)(playerPtr + 0x188); // player's current target/selected entity id
    }
  }
  if ((*this >> 1 & 1) != 0) {
    playerPtr = FUN_0078e110();
    if (playerPtr != 0) {
      secondId = *(uint *)(playerPtr + 0x188);
    }
  }

  // Condition: if either id is set, id must match firstId (or secondId if also set)
  if ((((firstId != 0) || (secondId != 0)) && (id != firstId)) &&
      ((secondId == 0) || (id == secondId))) {
    return 0;
  }
  return 1;
}