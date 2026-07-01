// FUNC_NAME: AudioManager::playSoundEffect
undefined1 AudioManager::playSoundEffect(undefined8 *param_1)
{
  undefined1 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 local_18;
  float fStack_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  // Allocate memory for two 32-bit values (likely a 2D position or two sound parameters)
  puVar2 = (undefined4 *)FUN_009c8e80(8);
  uVar3 = FUN_0043b490(); // Get first sound parameter (e.g., x-coordinate or volume)
  *puVar2 = uVar3;
  uVar3 = FUN_0043b490(); // Get second sound parameter (e.g., y-coordinate or pitch)
  puVar2[1] = uVar3;
  local_10 = *(undefined4 *)(param_1 + 1); // +0x08: some field from param_1
  fStack_14 = (float)((ulonglong)*param_1 >> 0x20); // Extract high 32 bits of param_1[0] as float
  _local_18 = CONCAT44(fStack_14 + _DAT_00d5cf70,(int)*param_1); // Add global offset to high part, combine with low part
  puVar4 = (undefined4 *)FUN_00555290(); // Get some global state (e.g., audio system)
  local_c = *puVar4; // Copy first 3 fields from that state
  local_8 = puVar4[1];
  local_4 = puVar4[2];
  uVar1 = FUN_0054ebf0(&local_c,&local_18,0x60122,0x10000,puVar2,2,0,0,0); // Play sound with parameters
  FUN_009c8f10(puVar2); // Free allocated memory
  return uVar1;
}