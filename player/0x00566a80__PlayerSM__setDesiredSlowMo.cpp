// FUNC_NAME: PlayerSM::setDesiredSlowMo
void __thiscall PlayerSM::setDesiredSlowMo(int this, char enableSlowMo)

{
  // Check if we have a player controller (offset +0x8)
  int *playerController = *(int **)(this + 8);
  if (playerController != (int *)0x0) {
    // Set slow motion flag on the controller (offset +0x33c)
    *(char *)(*playerController + 0x33c) = enableSlowMo;
  }
  
  // Update local state flags at offset +0x2c (bit 0)
  if (enableSlowMo != '\0') {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) | 1;  // Set slow Mo flag
    return;
  }
  *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) & 0xfffffffe;  // Clear slow Mo flag
  return;
}