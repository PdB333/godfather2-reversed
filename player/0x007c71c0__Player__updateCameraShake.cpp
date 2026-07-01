// FUNC_NAME: Player::updateCameraShake
void __fastcall Player::updateCameraShake(int *this)
{
  int playerPtr;
  int shakeType;
  
  playerPtr = FUN_007ab1e0(); // GetPlayer() - returns current player object
  if ((playerPtr == 0) || ((*(uint *)(this[0x16] + 0x8e0) >> 10 & 1) == 0)) {
    // No player or camera shake disabled (bit 10 of flags at +0x8e0)
    shakeType = this[0x46]; // +0x118 - current shake type
  }
  else {
    shakeType = this[0x46]; // +0x118 - current shake type
    if (*(char *)(playerPtr + 0x1aa) == '\x02') { // Player state == 2 (driving?)
      shakeType = (-(uint)(shakeType != 2) & 0x57584271) + 0x495c40e9;
      goto LAB_007c7216;
    }
  }
  shakeType = (-(uint)(shakeType != 2) & 0xb934f5a3) + 0xd2f35030;
LAB_007c7216:
  // Call virtual function at vtable+0x2c (SetCameraShake?)
  (**(code **)(*this + 0x2c))(shakeType, 1, 0, 0, 0x3f800000, 0x3f800000); // 1.0f, 1.0f
  return;
}