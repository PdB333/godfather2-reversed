// FUNC_NAME: NPC::processWeaponPickup
void __thiscall NPC::processWeaponPickup(int this, int *weaponData)
{
  int npcData;
  undefined4 *matrixPtr;
  int temp1;
  int temp2;
  float10 randFloat;
  float threshold;
  
  npcData = *(int *)(this + 8);
  if (((npcData != 0) && (*(char *)(npcData + 2) != '\0')) &&
     (threshold = (float)(weaponData[6] & DAT_00e44680), *(float *)(npcData + 0x14) <= threshold)) {
    *(undefined1 *)(npcData + 1) = 1;
    *(float *)(*(int *)(this + 8) + 0x18) = threshold;
    FUN_005403e0(0xd2); // Play pickup sound effect
    matrixPtr = (undefined4 *)weaponData[3];
    npcData = *(int *)(this + 8);
    *(undefined4 *)(npcData + 0x24) = *matrixPtr;
    *(undefined4 *)(npcData + 0x28) = matrixPtr[1];
    *(undefined4 *)(npcData + 0x2c) = matrixPtr[2];
    temp1 = weaponData[3];
    temp2 = *(int *)(this + 8);
    *(undefined4 *)(temp2 + 0x30) = *(undefined4 *)(temp1 + 0x10);
    *(undefined4 *)(temp2 + 0x34) = *(undefined4 *)(temp1 + 0x14);
    *(undefined4 *)(temp2 + 0x38) = *(undefined4 *)(temp1 + 0x18);
    temp1 = *weaponData;
    if (*(char *)(temp1 + 0x18) != '\x01') {
      *(undefined1 *)(*(int *)(this + 8) + 4) = 0;
      FUN_00540410(); // Finalize pickup (non-aimable weapon)
      return;
    }
    temp2 = weaponData[3];
    temp1 = *(int *)(this + 8);
    *(undefined4 *)(temp1 + 0x48) = *(undefined4 *)(temp2 + 0x10);
    *(undefined4 *)(temp1 + 0x4c) = *(undefined4 *)(temp2 + 0x14);
    *(undefined4 *)(temp1 + 0x50) = *(undefined4 *)(temp2 + 0x18);
    temp2 = *(int *)(this + 8);
    temp1 = *(char *)(weaponData[0] + 0x10) + weaponData[0];
    *(undefined4 *)(temp2 + 0x3c) = *(undefined4 *)(*(char *)(*weaponData + 0x10) + 0x1a0 + *weaponData);
    *(undefined4 *)(temp2 + 0x40) = *(undefined4 *)(temp1 + 0x1a4);
    *(undefined4 *)(temp2 + 0x44) = *(undefined4 *)(temp1 + 0x1a8);
    randFloat = (float10)FUN_009efd10(); // Random number generation
    *(float *)(*(int *)(this + 8) + 0x20) = (float)randFloat;
    *(undefined1 *)(*(int *)(this + 8) + 4) = 1;
    FUN_00540410(); // Finalize pickup (aimable weapon)
    return;
  }
  return;
}