// FUNC_NAME: MissionCheckpointManager::activateCheckpoint
undefined4 __thiscall FUN_00772de0(int this, int checkpoint, undefined4 param3, char param4, undefined4 param5)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  cVar1 = '\0';
  // Check if mission scene is ready, and whether this checkpoint's vehicle is valid (not 0 or 0x48 = 72, likely a special "no vehicle" ID)
  if (((*(int *)(*(int *)(this + 0xa0) + 0x1f3c) == 0) || (*(int *)(this + 0xb0) == 0)) ||
      (*(int *)(this + 0xb0) == 0x48)) goto LAB_00772eaf;
  
  // Reset activation timestamp and clear certain flags
  *(undefined4 *)(this + 0x74) = 0;
  *(uint *)(this + 0x9c) = *(uint *)(this + 0x9c) & 0xfffffffb; // Clear bit 2
  
  // Set or clear the "active" flag (bit 0) based on param4
  if (param4 == '\0') {
    *(uint *)(this + 0x9c) = *(uint *)(this + 0x9c) & 0xfffffffe; // Clear bit 0
  } else {
    *(uint *)(this + 0x9c) = *(uint *)(this + 0x9c) | 1; // Set bit 0
  }
  
  // Store the checkpoint reference
  *(int *)(this + 0x74) = checkpoint;
  
  // Check if the checkpoint has a "hasVehicle" flag (bit 8 of +0x24)
  if (((*(uint *)(checkpoint + 0x24) >> 8 & 1) == 0) || (param4 == '\0')) {
    // No vehicle requirement, or we are deactivating
    if ((*(byte *)(this + 0x9c) & 1) == 0) goto LAB_00772e8d; // If not active, jump to common code
    
    // Get vehicle type from checkpoint (0x48 = 72, or some offset)
    if (*(int *)(this + 0xb0) == 0) {
      iVar3 = 0;
    } else {
      iVar3 = *(int *)(this + 0xb0) + -0x48;
    }
    cVar1 = FUN_007cab20(*(undefined4 *)(checkpoint + 0xc),*(undefined4 *)(this + 0xa0),iVar3);
    uVar2 = *(undefined4 *)(checkpoint + 0x14);
  } else {
    // Checkpoint requires a vehicle, set the "vehicle requested" flag (bit 2)
    *(uint *)(this + 0x9c) = *(uint *)(this + 0x9c) | 4;
    
    // Spawn vehicle for this checkpoint
    FUN_006fbc40(&LAB_007ca9a0, this + 0x70); // Push vehicle spawn arg
    cVar1 = FUN_007e8700(*(undefined4 *)(this + 0xa0), 1); // Request vehicle spawn
    FUN_006fbc70(); // Pop args
    
LAB_00772e8d:
    uVar2 = *(undefined4 *)(checkpoint + 0x1c);
  }
  
  // Common handling: set up checkpoint trigger and its position
  uVar2 = FUN_00772930(uVar2, param3);
  FUN_00772a60(uVar2, param5);
  
  if (cVar1 != '\0') {
    return 1; // Vehicle spawn succeeded or not needed
  }
  
LAB_00772eaf:
  if (param4 == '\0') {
    return 1; // Deactivation always succeeds
  }
  return 0; // Activation failed
}