// FUNC_NAME: PlayerActionableInfo::updateActionableTargets
void __fastcall PlayerActionableInfo::updateActionableTargets(int this)
{
  float fVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  // Clear current actionable target data
  **(undefined1 **)(this + 0x20) = 0;  // +0x20: currentTargetName (string pointer)
  uVar7 = 0;
  *(undefined4 *)(this + 0x24) = 0;   // +0x24: currentTargetId
  **(undefined1 **)(this + 0x28) = 0; // +0x28: currentTargetDisplayName
  *(undefined4 *)(this + 0x2c) = 0;   // +0x2c: previousTargetId
  *(undefined4 *)(this + 0x30) = 0;   // +0x30: some flag
  *(undefined4 *)(this + 0x40) = 0;   // +0x40: newTargetId
  *(undefined4 *)(this + 0x34) = 0;   // +0x34: some other flag
  
  iVar3 = FUN_008c74d0(*(undefined4 *)(this + 0x1c));  // Get entity from entity ID
  if (iVar3 != 0) {
    puVar4 = *(undefined1 **)(iVar3 + 0x8c);  // +0x8c: entity name
    if (puVar4 == (undefined1 *)0x0) {
      puVar4 = &DAT_0120546e;  // Empty string fallback
    }
    FUN_005c4660(*(undefined4 *)(this + 0x20), puVar4, 0x20, *(undefined4 *)(iVar3 + 0x90));  // Copy entity name
    fVar1 = *(float *)(iVar3 + 0x100);  // +0x100: entity type ID (stored as float)
    *(int *)(this + 0x24) = (int)fVar1;  // Store entity type ID
    
    local_10 = (undefined1 *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code *)0x0;
    FUN_00604000((int)fVar1, &local_10, 1);  // Get display name for entity type
    puVar4 = local_10;
    if (local_10 == (undefined1 *)0x0) {
      puVar4 = &DAT_0120546e;  // Empty string fallback
    }
    FUN_005c4660(*(undefined4 *)(this + 0x28), puVar4, 0x20, local_c);  // Copy display name
    
    iVar3 = DAT_0112a590;  // Global entity manager
    if (*(int *)(DAT_0112a590 + 0xc) != 0) {  // +0xc: entity count
      do {
        puVar2 = *(undefined4 **)(*(int *)(iVar3 + 8) + uVar7 * 4);  // Get entity at index
        if ((puVar2 != (undefined4 *)0x0) &&
           (iVar5 = FUN_0084a410(), *(int *)(this + 0x1c) == iVar5)) {  // Check if entity matches
          puVar6 = (undefined4 *)FUN_00929da0();  // Allocate new target data
          *puVar6 = *(undefined4 *)*puVar2;  // Copy entity data
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(iVar3 + 0xc));  // Iterate through all entities
    }
    *(undefined4 *)(this + 0x2c) = *(undefined4 *)(this + 0x40);  // Update previous target ID
    
    if (local_10 != (undefined1 *)0x0) {
      (*local_4)(local_10);  // Free display name string
    }
  }
  return;
}