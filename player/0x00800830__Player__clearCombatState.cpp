// FUNC_NAME: Player::clearCombatState
void __fastcall Player::clearCombatState(int thisPtr)
{
  // Check if current combat state is not idle (0) and not a specific state (0x48)
  if ((*(int *)(thisPtr + 0x74c) != 0) && (*(int *)(thisPtr + 0x74c) != 0x48)) {
    // Exit current combat state
    FUN_00707a40();
  }
  // Check if the "in combat" flag (bit 10) is set in the player flags at +0x8e0
  if ((*(uint *)(thisPtr + 0x8e0) >> 10 & 1) != 0) {
    // Call a virtual function at vtable+0x28 with parameter 0x20 (likely a state change or animation trigger)
    (**(code **)(*(int *)(thisPtr + 0x58) + 0x28))(0x20);
  }
  // Clear the "in combat" flag (bit 10) in the player flags
  *(uint *)(thisPtr + 0x8e0) = *(uint *)(thisPtr + 0x8e0) & 0xfffffbff;
  return;
}